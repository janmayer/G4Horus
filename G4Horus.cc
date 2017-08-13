#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

#include "G4MTRunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "QGSP_INCLXX_HP.hh"

#include <algorithm>
#include <string>

inline std::string GetCmdOption(char** begin, char** end,
                                const std::string& option,
                                const std::string& def = "")
{
    char** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return std::string(*itr);
    }
    return def;
}

inline bool CmdOptionExists(char** begin, char** end,
                            const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char* argv[])
{
    if (CmdOptionExists(argv, argv + argc, "-h") || CmdOptionExists(argv, argv + argc, "--help")) {
        G4cout << "G4Horus - Gamma-ray detection efficiency simulation." << G4endl;
        G4cout << "Usage: G4Horus ([-m macro] [-t threads] | [-h])" << G4endl;
        G4cout << "    -m macro    Process macro file in batch mode" << G4endl;
        G4cout << "    -t threads  Number of threads for event processing" << G4endl;
        G4cout << "    -h          Print this message" << G4endl;
        return 0;
    }

    G4int threads = 1;
    if (CmdOptionExists(argv, argv + argc, "-t")) {
        try {
            threads = std::stoi(GetCmdOption(argv, argv + argc, "-t", "0"));
        } catch (...) {
            G4cerr << "Invalid number of threads." << G4endl;
            return 1;
        }
        if (threads < 1) {
            threads = 1;
        }
    }

    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    auto run_manager = new G4MTRunManager();
    run_manager->SetUserInitialization(new DetectorConstruction());
    run_manager->SetUserInitialization(new QGSP_INCLXX_HP);
    run_manager->SetUserInitialization(new ActionInitialization());
    run_manager->SetNumberOfThreads(threads);
    run_manager->Initialize();

    auto ui_manager = G4UImanager::GetUIpointer();
    if (CmdOptionExists(argv, argv + argc, "-m")) {
        G4String macro = GetCmdOption(argv, argv + argc, "-m");
        ui_manager->ApplyCommand("/control/execute " + macro);
    } else {
        // Note: Order matters, segmentation fault otherwise!
        auto vis_manager = new G4VisExecutive;
        vis_manager->Initialize();

        auto ui = new G4UIExecutive(argc, argv, G4String());
        ui_manager->ApplyCommand("/control/execute vis.mac");
        ui_manager->ApplyCommand("/control/execute gui.mac");
        ui->SessionStart();
        delete ui;

        delete vis_manager;
    }

    delete run_manager;
    return 0;
}
