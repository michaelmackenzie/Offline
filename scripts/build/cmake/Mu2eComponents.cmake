# Mu2eComponents.cmake -- select which Offline packages the CMake build configures.
#
# Offline is divided into build components listed in scripts/build/components.txt
# (dataproducts, core, reco, mcdataproducts, simbase, g4, sim; see the header of that file for the format).  Every
# top-level package belongs to exactly one component.  The same manifest drives the SCons
# build (env var MU2E_COMPONENTS) and is checked by plan/tools/check_components.py.
#
# HOW TO SELECT
#   cmake -DMU2E_COMPONENTS=reco ...            # reco and everything it requires (core)
#   cmake -DMU2E_COMPONENTS="reco,g4" ...       # comma or semicolon separated list
#   cmake ...                                   # default: all
#
# Rules
#   * A selection is expanded through the `requires` of each component, transitively.
#   * Unknown component names are a FATAL_ERROR.
#   * `all` selects every component.  With WITH_G4 false (the "trig" UPS qualifier, or
#     -DWITH_G4=FALSE) the components marked `needs-geant4` are dropped from `all`, which
#     is what the trig build has always done.
#   * Explicitly selecting a `needs-geant4` component (or one that requires it) with
#     WITH_G4 false is a FATAL_ERROR.
#   * Every directory passed to mu2e_add_package() must be listed in the manifest
#     (FATAL_ERROR otherwise), so a new package cannot be forgotten.
#
# `dataproducts` is the smallest component: DataProducts, RecoDataProducts and their minimal
# dependencies (GeneralUtilities, BTrkLegacy, GlobalConstantsService, ConfigTools, Mu2eInterfaces,
# DbTables), with no geometry, conditions or KinKal-geometry packages.  `mcdataproducts` (side sim)
# adds MCDataProducts on top of it.  Select them like any other component, e.g.
#   cmake -DMU2E_COMPONENTS=dataproducts ...
#   cmake -DMU2E_COMPONENTS="dataproducts,mcdataproducts" ...
#
# PROVIDED
#   mu2e_add_package(<dir>)       add_subdirectory(<dir>) iff its component is selected
#   mu2e_package_selected(<dir> <var>)   set <var> to TRUE/FALSE
#   Offline_COMPONENTS            expanded, selected component list
#   Offline_HAS_<COMP>            TRUE/FALSE for each component (DATAPRODUCTS, CORE, RECO, MCDATAPRODUCTS, SIMBASE, G4, SIM)
#   Offline_PACKAGES              list of selected packages
# The last three are also written into the installed OfflineConfig.cmake (see
# Mu2eComponentsConfig.cmake.in) so downstream projects can do:
#   find_package(Offline REQUIRED)
#   if(NOT Offline_HAS_SIM) ... endif()
#   list(FIND Offline_COMPONENTS reco i)

set(MU2E_COMPONENTS "all" CACHE STRING
  "Offline build components to build (list of names or 'all'); see scripts/build/cmake/Mu2eComponents.cmake")

set(_mu2e_manifest "${CMAKE_CURRENT_LIST_DIR}/../components.txt")
get_filename_component(_mu2e_manifest "${_mu2e_manifest}" ABSOLUTE)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${_mu2e_manifest}")

# ---- parse the manifest ------------------------------------------------------------
set(_mu2e_all_comps)
set(_mu2e_all_pkgs)
file(STRINGS "${_mu2e_manifest}" _mu2e_lines)
foreach(_line IN LISTS _mu2e_lines)
  string(REGEX REPLACE "#.*$" "" _line "${_line}")
  string(STRIP "${_line}" _line)
  if(_line STREQUAL "")
    continue()
  endif()
  string(REGEX REPLACE "[ \t]+" ";" _f "${_line}")
  list(GET _f 0 _first)
  if(_first STREQUAL "component")
    list(GET _f 1 _name)
    list(APPEND _mu2e_all_comps ${_name})
    set(_mu2e_comp_${_name}_requires)
    set(_mu2e_comp_${_name}_g4 FALSE)
    set(_mode)
    list(REMOVE_AT _f 0 1)
    while(_f)
      list(POP_FRONT _f _w)
      if(_w STREQUAL "side")
        list(POP_FRONT _f _side)
      elseif(_w STREQUAL "requires")
        set(_mode requires)
      elseif(_w STREQUAL "needs-geant4")
        set(_mu2e_comp_${_name}_g4 TRUE)
      elseif(_mode STREQUAL "requires")
        list(APPEND _mu2e_comp_${_name}_requires ${_w})
      else()
        message(FATAL_ERROR "${_mu2e_manifest}: cannot parse line: ${_line}")
      endif()
    endwhile()
  else()
    list(LENGTH _f _n)
    if(NOT _n EQUAL 2)
      message(FATAL_ERROR "${_mu2e_manifest}: expected '<Package> <component>': ${_line}")
    endif()
    list(GET _f 1 _c)
    set(_mu2e_pkg_${_first} ${_c})
    list(APPEND _mu2e_all_pkgs ${_first})
  endif()
endforeach()
foreach(_p IN LISTS _mu2e_all_pkgs)
  if(NOT _mu2e_pkg_${_p} IN_LIST _mu2e_all_comps)
    message(FATAL_ERROR "${_mu2e_manifest}: package ${_p} names unknown component ${_mu2e_pkg_${_p}}")
  endif()
endforeach()

# ---- expand the selection ------------------------------------------------------------
string(REPLACE "," ";" _mu2e_req "${MU2E_COMPONENTS}")
string(REPLACE " " ";" _mu2e_req "${_mu2e_req}")
list(REMOVE_ITEM _mu2e_req "")
if(NOT _mu2e_req)
  set(_mu2e_req all)
endif()

set(_mu2e_select_all FALSE)
set(_mu2e_todo)
foreach(_c IN LISTS _mu2e_req)
  if(_c STREQUAL "all")
    set(_mu2e_select_all TRUE)
  elseif(_c IN_LIST _mu2e_all_comps)
    list(APPEND _mu2e_todo ${_c})
  else()
    string(REPLACE ";" " " _known "${_mu2e_all_comps}")
    message(FATAL_ERROR "MU2E_COMPONENTS: unknown component '${_c}'. Known: all ${_known}")
  endif()
endforeach()
if(_mu2e_select_all)
  set(_mu2e_todo ${_mu2e_all_comps})
endif()

set(_mu2e_sel)
while(_mu2e_todo)
  list(POP_FRONT _mu2e_todo _c)
  if(_c IN_LIST _mu2e_sel)
    continue()
  endif()
  list(APPEND _mu2e_sel ${_c})
  foreach(_r IN LISTS _mu2e_comp_${_c}_requires)
    if(NOT _r IN_LIST _mu2e_all_comps)
      message(FATAL_ERROR "${_mu2e_manifest}: component ${_c} requires unknown component ${_r}")
    endif()
    list(APPEND _mu2e_todo ${_r})
  endforeach()
endwhile()

# keep manifest order
set(_mu2e_ordered)
foreach(_c IN LISTS _mu2e_all_comps)
  if(_c IN_LIST _mu2e_sel)
    list(APPEND _mu2e_ordered ${_c})
  endif()
endforeach()
set(_mu2e_sel ${_mu2e_ordered})

# Geant4 interaction
set(_mu2e_dropped)
if(NOT WITH_G4)
  foreach(_c IN LISTS _mu2e_sel)
    if(_mu2e_comp_${_c}_g4)
      if(_mu2e_select_all)
        list(APPEND _mu2e_dropped ${_c})
      else()
        message(FATAL_ERROR
          "MU2E_COMPONENTS='${MU2E_COMPONENTS}' selects component '${_c}', which needs Geant4, "
          "but WITH_G4 is false (trig qualifier or -DWITH_G4=FALSE). Re-configure with "
          "-DWITH_G4=TRUE, or choose components that do not need Geant4.")
      endif()
    endif()
  endforeach()
  if(_mu2e_dropped)
    list(REMOVE_ITEM _mu2e_sel ${_mu2e_dropped})
  endif()
endif()

set(Offline_COMPONENTS ${_mu2e_sel})
foreach(_c IN LISTS _mu2e_all_comps)
  string(TOUPPER ${_c} _C)
  if(_c IN_LIST Offline_COMPONENTS)
    set(Offline_HAS_${_C} TRUE)
  else()
    set(Offline_HAS_${_C} FALSE)
  endif()
endforeach()
set(Offline_ALL_COMPONENTS ${_mu2e_all_comps})

set(Offline_PACKAGES)
foreach(_p IN LISTS _mu2e_all_pkgs)
  if(_mu2e_pkg_${_p} IN_LIST Offline_COMPONENTS)
    list(APPEND Offline_PACKAGES ${_p})
  endif()
endforeach()

string(REPLACE ";" " " _s "${Offline_COMPONENTS}")
list(LENGTH Offline_PACKAGES _np)
list(LENGTH _mu2e_all_pkgs _nall)
message(STATUS "Offline components: MU2E_COMPONENTS='${MU2E_COMPONENTS}' WITH_G4=${WITH_G4} -> ${_s} (${_np}/${_nall} packages)")
if(_mu2e_dropped)
  string(REPLACE ";" " " _d "${_mu2e_dropped}")
  message(STATUS "Offline components: dropped (need Geant4, WITH_G4 false): ${_d}")
endif()

# ---- public helpers --------------------------------------------------------------------
function(mu2e_package_selected dir var)
  if(NOT DEFINED _mu2e_pkg_${dir})
    message(FATAL_ERROR "Package '${dir}' is not listed in ${_mu2e_manifest}; add a line '<Package> <component>'")
  endif()
  if(_mu2e_pkg_${dir} IN_LIST Offline_COMPONENTS)
    set(${var} TRUE PARENT_SCOPE)
  else()
    set(${var} FALSE PARENT_SCOPE)
  endif()
endfunction()

# add_subdirectory() only if the package's component is selected.  Macro so that
# add_subdirectory runs in the caller's scope.
macro(mu2e_add_package dir)
  mu2e_package_selected(${dir} _mu2e_sel_${dir})
  if(_mu2e_sel_${dir})
    add_subdirectory(${dir})
  else()
    message(VERBOSE "Offline components: skipping ${dir} (component ${_mu2e_pkg_${dir}})")
  endif()
endmacro()

# Fragment for the installed OfflineConfig.cmake, passed to cet_cmake_config(CONFIG_POST_INIT).
set(MU2E_COMPONENTS_CONFIG_FRAGMENT "${CMAKE_CURRENT_BINARY_DIR}/Mu2eComponentsConfig.cmake")
set(_frag "# Offline build components (generated by Mu2eComponents.cmake)\n")
# unquoted, space separated: the fragment is re-configured, which would mangle ';'
string(REPLACE ";" " " _frag_sel "${Offline_COMPONENTS}")
string(REPLACE ";" " " _frag_all "${Offline_ALL_COMPONENTS}")
string(APPEND _frag "set(Offline_COMPONENTS ${_frag_sel})\n")
string(APPEND _frag "set(Offline_ALL_COMPONENTS ${_frag_all})\n")
foreach(_c IN LISTS _mu2e_all_comps)
  string(TOUPPER ${_c} _C)
  string(APPEND _frag "set(Offline_HAS_${_C} ${Offline_HAS_${_C}})\n")
endforeach()
file(WRITE "${MU2E_COMPONENTS_CONFIG_FRAGMENT}" "${_frag}")
