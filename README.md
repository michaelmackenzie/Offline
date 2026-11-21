# Offline
Offline software for the Mu2e experiment at Fermilab.


## Building a subset (build components)
Top-level packages are grouped into components (`core`, `reco`, `simbase`, `g4`, `sim`) in
`scripts/build/components.txt`. With CMake, select components at configure time:

    cmake -DMU2E_COMPONENTS=reco ...          # reco plus what it requires (core)
    cmake -DMU2E_COMPONENTS="reco,g4" ...     # comma or semicolon separated
    cmake ...                                 # default: all

Names are expanded through `requires`; unknown names are an error; `g4` (Geant4) needs
`-DWITH_G4=TRUE` (`all` silently drops it when WITH_G4 is false, as the trig build does).
Downstream projects see the selection as `Offline_COMPONENTS` and `Offline_HAS_<COMP>`
(e.g. `Offline_HAS_SIM`) after `find_package(Offline)`. Details and the planned small
`dataproducts` component: `scripts/build/cmake/Mu2eComponents.cmake`.
