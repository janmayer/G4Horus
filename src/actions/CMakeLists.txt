project(G4HorusActions)

add_library(${PROJECT_NAME}
            ActionInitialization.cc
            EventActionHistogram.cc
            EventActionNtuple.cc
            EventActionSoco.cc
            PrimaryGeneratorAction.cc
            PrimaryGeneratorActionScattering.cc
            PrimaryGeneratorScattering.cc
            RunActionHistogram.cc
            RunActionNtuple.cc
            RunActionSoco.cc)
add_library(G4Horus::actions ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} G4Horus::soco)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
