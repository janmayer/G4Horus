project(G4HorusDetectors)

add_library(${PROJECT_NAME}
            BGO.cc
            Detector.cc
            DetectorLibrary.cc
            HPGe.cc
            HPGeClover.cc
            HPGeCoaxial.cc
            HPGeHexagonal.cc
            PIPS.cc)
add_library(G4Horus::detectors ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
