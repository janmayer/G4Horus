#include "ActionInitialization.hh"
#include "EventActionHistogram.hh"
#include "EventActionNtuple.hh"
#include "EventActionSoco.hh"
#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorActionScattering.hh"
#include "RunActionHistogram.hh"
#include "RunActionNtuple.hh"
#include "RunActionSoco.hh"

// Build() and BuildForMaster() have to be able to create new instances of Run and Event Actions.
// To be able to choose different actions, create creators (~factories) for the different types.
template <typename T>
G4UserRunAction *createRunAction() { return new T; }
template <typename T>
G4UserEventAction *createEventAction() { return new T; }

const std::map<std::string, std::pair<ActionInitialization::RunActionCreator, ActionInitialization::EventActionCreator>> knownModes(
    {
        {"hist", {&createRunAction<RunActionHistogram>, &createEventAction<EventActionHistogram>}},
        {"ntuple", {&createRunAction<RunActionNtuple>, &createEventAction<EventActionNtuple>}},
        {"soco", {&createRunAction<RunActionSoco>, &createEventAction<EventActionSoco>}},
    });

ActionInitialization::ActionInitialization(const std::string &mode)
{
    auto m = knownModes.find(mode);
    if (m == knownModes.end()) {
        G4Exception("ActionInitialization", "Unknown mode", FatalException, ("Output Mode " + mode + " has no Action Creations.").c_str());
    }
    fRunActionCreator = m->second.first;
    fEventActionCreator = m->second.second;
}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(fRunActionCreator());
}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction);
    // SetUserAction(new PrimaryGeneratorActionScattering);
    SetUserAction(fRunActionCreator());
    SetUserAction(fEventActionCreator());
}
