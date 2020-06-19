project(G4HorusGeometries)

add_library(${PROJECT_NAME}
            AstroTargetkammer.cc
            AstroTargetkammerV2.cc
            CADElement.cc
            CologneCloverSetup.cc
            DummyChamber.cc
            Horus.cc
            Setup.cc
            SONIC.cc
            SonicV3.cc
            SonicV3dEE.cc)
add_library(G4Horus::geometries ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} G4Horus::detectors)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
