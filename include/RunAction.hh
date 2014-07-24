#ifndef RUNACTION_H
#define RUNACTION_H

#include "globals.hh"
#include "G4UserRunAction.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif //RUNACTION_H
