project(G4HorusGeometries)

add_library(${PROJECT_NAME}
            AstroTargetkammer.cc
            CologneCloverSetup.cc
            DummyChamber.cc
            Horus.cc
            Setup.cc
            SONIC.cc
            SonicV3.cc)
add_library(G4Horus::geometries ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${CADMESH_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} G4Horus::detectors)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
