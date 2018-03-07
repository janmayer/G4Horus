cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

project(G4HORUS)

# Give an error and terminate if the compiler does not support C++11
# Enable C++11 standard and optimization
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if(NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.\nPlease enable a non-ancient devtoolset.")
    endif()
endif()
add_definitions("-std=c++11 -O3 -Wall -Wextra -g")

# Find Geant4 package, activating all available UI and Vis drivers by default
# Setup Geant4 include directories and compile definitions
find_package(Geant4 10.4 REQUIRED ui_all vis_all multithreaded)
include(${Geant4_USE_FILE})
message(STATUS "Geant4 Version: ${Geant4_VERSION}")
message(STATUS "Geant4 Include Dir: ${Geant4_INCLUDE_DIRS}")

# Include CADMesh for importing stl geometries
find_package(cadmesh REQUIRED)

# Setup include directory for this project
include_directories(
        ${CADMESH_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/actions
        ${PROJECT_SOURCE_DIR}/src/detectors
        ${PROJECT_SOURCE_DIR}/src/geometries
        ${PROJECT_SOURCE_DIR}/src/soco
)

# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/src/*.hh)

# Add the executable, and link it to the Geant4 libraries
add_executable(G4Horus G4Horus.cc ${sources} ${headers})
target_link_libraries(G4Horus ${Geant4_LIBRARIES} ${cadmesh_LIBRARIES})

# Copy all scripts to the build directory, i.e. the directory in which we
# build B4c. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
file(GLOB G4Horus_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts/*.mac)
foreach(_file ${G4Horus_SCRIPTS})
    get_filename_component(_script ${_file} NAME)
    configure_file(
        ${_file}
        ${PROJECT_BINARY_DIR}/${_script}
        COPYONLY
    )
endforeach()
