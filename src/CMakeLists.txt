add_subdirectory(actions)
add_subdirectory(detectors)
add_subdirectory(soco)
add_subdirectory(geometries)

project(G4HorusConstruction)

add_library(${PROJECT_NAME} DetectorConstruction.cc)
add_library(G4Horus::construction ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} G4Horus::detectors G4Horus::geometries)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
