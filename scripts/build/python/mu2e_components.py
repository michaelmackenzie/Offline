"""Build-component selection for the SCons (muse) build.

The package -> component map and the component `requires` graph live in
scripts/build/components.txt (same file the CMake build reads).  Every SConscript starts
with a guard that asks this module whether its package is selected, and returns if not.

Usage
-----
    MU2E_COMPONENTS=reco muse build -j 8          # reco + everything it requires (core)
    MU2E_COMPONENTS=core,simbase muse build ...   # comma or space separated list
    muse build ...                                # unset, empty or 'all': everything (as before)

Component names are those in components.txt; each selection is expanded through `requires`.
An unknown name is an error.  In muse trigger mode (env['TRIGGER']=='on', i.e. MUSE_TRIGGER
set) components marked `needs-geant4` are dropped from `all`, and explicitly selecting one
(or one that requires it) is an error.

Caveats
-------
* The selection is NOT remembered by the build area.  muse/SCons just see fewer SConscripts,
  so libraries/plugins from a previous, larger build stay in lib/ and keep being found.  Use
  a separate build area per selection (e.g. a separate workspace/build symlink), or run
  plan/tools/clean_stale_plugins.py after changing the selection.  Set the same
  MU2E_COMPONENTS for every `muse build` in a given area.
* A cleaner future route is a muse option (e.g. `muse setup ... reco`) that stores the
  selection with the build area; this module would then take it from there.
* The manifest check is plan/tools/check_components.py (also checks every SConscript has the guard).

Python API: selected_components(trigger=False) -> set of components;
selected_packages(...) -> set of packages; is_selected(pkg, trigger=False) -> bool;
guard(sconscript_path, trigger) -> bool (used by the SConscript guard).
"""
import os
import re

ENVVAR = 'MU2E_COMPONENTS'
_cache = {}


def manifest_path():
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'components.txt')


def parse_manifest(path=None):
    """returns (comps, pkgs): comps {name: {'requires': [...], 'g4': bool}}, pkgs {package: component}"""
    path = path or manifest_path()
    comps, pkgs = {}, {}
    for line in open(path):
        t = line.split('#', 1)[0].split()
        if not t:
            continue
        if t[0] == 'component':
            c = {'requires': [], 'g4': False}
            i = 2
            while i < len(t):
                if t[i] == 'side':
                    i += 2
                elif t[i] == 'requires':
                    i += 1
                    while i < len(t) and t[i] not in ('needs-geant4', 'side'):
                        c['requires'].append(t[i])
                        i += 1
                elif t[i] == 'needs-geant4':
                    c['g4'] = True
                    i += 1
                else:
                    i += 1
            comps[t[1]] = c
        elif len(t) == 2:
            pkgs[t[0]] = t[1]
    return comps, pkgs


def _closure(comps, name):
    seen, st = set(), [name]
    while st:
        c = st.pop()
        if c in seen:
            continue
        seen.add(c)
        st += comps[c]['requires']
    return seen


def selected_components(trigger=False, spec=None, path=None):
    """Components to build for spec (default: env MU2E_COMPONENTS), expanded through requires."""
    comps, _ = parse_manifest(path)
    if spec is None:
        spec = os.environ.get(ENVVAR, '')
    names = [s for s in re.split(r'[,\s]+', spec) if s]
    if not names or names == ['all']:
        want = set(comps)
        if trigger:
            want = {c for c in want if not (_closure(comps, c) & {g for g in comps if comps[g]['g4']})}
        return want
    want = set()
    for n in names:
        if n not in comps:
            raise ValueError("%s: unknown component '%s' (known: %s)" % (ENVVAR, n, ', '.join(comps)))
        want |= _closure(comps, n)
    if trigger:
        bad = sorted(c for c in want if comps[c]['g4'])
        if bad:
            raise ValueError("%s=%s selects component(s) %s which need Geant4, "
                             "but this is a trigger build (MUSE_TRIGGER set)" % (ENVVAR, spec, ', '.join(bad)))
    return want


def selected_packages(trigger=False, spec=None, path=None):
    comps, pkgs = parse_manifest(path)
    want = selected_components(trigger, spec, path)
    return {p for p, c in pkgs.items() if c in want}


def is_selected(pkg, trigger=False):
    key = (trigger, os.environ.get(ENVVAR, ''))
    if key not in _cache:
        _cache[key] = selected_packages(trigger)
    return pkg in _cache[key]


def guard(sconscript_path, trigger):
    """True if the package owning this SConscript is selected.  The package is the first
    directory below the repo root (the dir that holds scripts/build/components.txt)."""
    d = os.path.dirname(os.path.abspath(sconscript_path))
    pkg = None
    while d != os.path.dirname(d):
        if os.path.exists(os.path.join(d, 'scripts', 'build', 'components.txt')):
            break
        pkg, d = os.path.basename(d), os.path.dirname(d)
    else:
        raise RuntimeError('mu2e_components: no scripts/build/components.txt above ' + sconscript_path)
    if pkg is None:
        pkg = 'scripts'
    if pkg not in parse_manifest()[1]:
        raise RuntimeError('mu2e_components: package %s is not in components.txt' % pkg)
    return is_selected(pkg, trigger)
