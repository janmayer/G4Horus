project(G4HorusSoco)

add_library(${PROJECT_NAME}
            Event.cc
            Hit.cc
            SocoAnalysisManager.cc
            SocoFileMessenger.cc)
add_library(G4Horus::soco ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
