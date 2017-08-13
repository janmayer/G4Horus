#ifndef RUNACTION_H
#define RUNACTION_H

#include "G4UserRunAction.hh"

class G4Run;

class RunAction : public G4UserRunAction {
  public:
    RunAction();
    ~RunAction();

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
};

#endif //RUNACTION_H
