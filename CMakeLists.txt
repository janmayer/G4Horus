cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(G4Horus)

# Find Geant4 package, require all available UI and Vis drivers by default
find_package(Geant4 10.5 REQUIRED ui_all vis_all multithreaded)
# Unfortunately, Geant4 uses cmake ineptly and forces its settings upon us ...
include(${Geant4_USE_FILE})
message(STATUS "Geant4 Version:          ${Geant4_VERSION}")
message(STATUS "Geant4 Include Dir:      ${Geant4_INCLUDE_DIRS}")
message(STATUS "Geant4 Definitions:      ${Geant4_DEFINITIONS}")
message(STATUS "Geant4 Build Type:       ${Geant4_BUILD_TYPE}")
# ... so we add our flags to that
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
message(STATUS "CXX_FLAGS                ${CMAKE_CXX_FLAGS}")
message(STATUS "CXX_FLAGS_DEBUG          ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CXX_FLAGS_RELEASE        ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

# Include CADMesh for importing stl geometries
find_package(cadmesh REQUIRED)

add_subdirectory(src)

# Add the executable, and link it to the Geant4 libraries
add_executable(${PROJECT_NAME} G4Horus.cc)
target_link_libraries(${PROJECT_NAME}
                      G4Horus::construction
                      G4Horus::actions
                      ${Geant4_LIBRARIES}
                      ${cadmesh_LIBRARIES})
set_target_properties(${PROJECT_NAME}
                      PROPERTIES INTERPROCEDURAL_OPTIMIZATION True)
