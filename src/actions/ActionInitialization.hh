#pragma once

#include "G4VUserActionInitialization.hh"
#include <map>
#include <string>

class ActionInitialization : public G4VUserActionInitialization {
  public:
    explicit ActionInitialization(const std::string& mode);

    void BuildForMaster() const override;
    void Build() const override;

    using RunActionCreator = G4UserRunAction* (*)();
    using EventActionCreator = G4UserEventAction* (*)();

  private:
    RunActionCreator fRunActionCreator;
    EventActionCreator fEventActionCreator;
};
