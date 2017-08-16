#ifndef RUNACTION_H
#define RUNACTION_H

#include "G4UserRunAction.hh"

class G4Run;

class RunAction : public G4UserRunAction {
  public:
    RunAction();
    ~RunAction() override;
    RunAction(const RunAction&) = delete;
    RunAction(RunAction&&) = delete;
    RunAction& operator=(const RunAction&) = delete;
    RunAction& operator=(RunAction&&) = delete;

    void BeginOfRunAction(const G4Run* /*aRun*/) override;
    void EndOfRunAction(const G4Run* /*aRun*/) override;
};

#endif //RUNACTION_H
