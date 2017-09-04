#ifndef G4HORUS_RUNACTIONHISTOGRAM_H
#define G4HORUS_RUNACTIONHISTOGRAM_H

#include "G4UserRunAction.hh"

class G4Run;

class RunActionHistogram : public G4UserRunAction {
  public:
    RunActionHistogram();
    ~RunActionHistogram() override;
    RunActionHistogram(const RunActionHistogram&) = delete;
    RunActionHistogram(RunActionHistogram&&) = delete;
    RunActionHistogram& operator=(const RunActionHistogram&) = delete;
    RunActionHistogram& operator=(RunActionHistogram&&) = delete;

    void BeginOfRunAction(const G4Run* /*aRun*/) override;
    void EndOfRunAction(const G4Run* /*aRun*/) override;
};

#endif //G4HORUS_RUNACTIONHISTOGRAM_H
