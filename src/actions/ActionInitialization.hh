#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization {
  public:
    ActionInitialization() = default;

    void BuildForMaster() const override;
    void Build() const override;
};

#endif //ACTIONINITIALIZATION_HH
