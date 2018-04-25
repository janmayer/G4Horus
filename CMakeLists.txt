cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(G4HORUS)

# Find Geant4 package, activating all available UI and Vis drivers by default
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
add_executable(G4Horus G4Horus.cc ${sources})
target_link_libraries(G4Horus ${Geant4_LIBRARIES} ${cadmesh_LIBRARIES})

# Enable C++11 standard and optimization
# Give an error and terminate if the compiler does not support C++11
set_property(TARGET G4Horus PROPERTY CXX_STANDARD 11)
set_property(TARGET G4Horus PROPERTY CXX_STANDARD_REQUIRED ON)

# By default, we want an optimized build. Add debug info for conveience
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "" FORCE)
endif()

include(CheckCXXCompilerFlag)
# Use -Wextra if available
CHECK_CXX_COMPILER_FLAG("" COMPILER_SUPPORTS_WEXTRA)
if(COMPILER_SUPPORTS_WEXTRA)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif()
# Use march=native if available
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()
