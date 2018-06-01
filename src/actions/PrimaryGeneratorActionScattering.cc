#include "PrimaryGeneratorActionScattering.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4SIunits.hh"

PrimaryGeneratorScattering::LevelScheme BuildLevelScheme()
{
    PrimaryGeneratorScattering::LevelScheme ls;
    // clang-format off
    ls[0] = {0 * keV, {}};
    ls[1509] = {1509 * keV, {{1509 * keV, 100, 0},}};
    ls[2282] = {2282 * keV, {{773 * keV, 100, 1509},}};
    ls[2519] = {2519 * keV, {{1010 * keV, 100, 1509},}};
    ls[2526] = {2526 * keV, {{244 * keV, 100, 2282},}};
    ls[2612] = {2612 * keV, {{85 * keV, 13, 2526}, {329 * keV, 100, 2282},}};
    ls[2634] = {2634 * keV, {{2634 * keV, 100, 0},}};
    ls[2760] = {2760 * keV, {{148 * keV, 100, 2634},}};
    ls[2838] = {2838 * keV, {{2838 * keV, 100, 0},}};
    ls[2849] = {2849 * keV, {{567 * keV, 3.3, 2282}, {1340 * keV, 100, 1509},}};
    ls[2922] = {2922 * keV, {{2922 * keV, 100, 0},}};
    ls[3006] = {3006 * keV, {{157 * keV, 1, 2849}, {480 * keV, 100, 2526},}};
    ls[3063] = {3063 * keV, {{213 * keV, 7.3, 2849}, {536 * keV, 100, 2526},}};
    ls[3091] = {3091 * keV, {{1581 * keV, 21.6, 1509}, {3091 * keV, 100, 0},}};
    ls[3368] = {3368 * keV, {{305 * keV, 100, 3063}, {361 * keV, 27.5, 3006}, {842 * keV, 106, 2526}, {1085 * keV, 23.2, 2282}, {1858 * keV, 4.8, 1509},}};
    ls[3380] = {3380 * keV, {{1097 * keV, 100, 2282},}};
    ls[3384] = {3384 * keV, {{3384 * keV, 100, 0},}};
    ls[3542] = {3542 * keV, {{2032 * keV, 100, 1509}, {3541 * keV, 14.1, 0},}};
    ls[3579] = {3579 * keV, {{1052 * keV, 100, 2526}, {1297 * keV, 87, 2282}, {2070 * keV, 33, 1509},}};
    ls[3621] = {3621 * keV, {{2111 * keV, 100, 1509},}};
    ls[3624] = {3624 * keV, {{243 * keV, 0, 3380}, {1097 * keV, 100, 2526},}};
    ls[3651] = {3651 * keV, {{3651 * keV, 100, 0},}};
    ls[3688] = {3688 * keV, {{838 * keV, 15.8, 2849}, {2179 * keV, 100, 1509},}};
    ls[3753] = {3753 * keV, {{385 * keV, 100, 3368}, {689 * keV, 100, 3063},}};
    ls[3757] = {3757 * keV, {{1230 * keV, 100, 2526},}};
    ls[3814] = {3814 * keV, {{234 * keV, 91, 3579}, {750 * keV, 0, 3063}, {807 * keV, 36.1, 3006}, {964 * keV, 94, 2849}, {2305 * keV, 100, 1509},}};
    ls[3841] = {3841 * keV, {{2332 * keV, 100, 1509},}};
    ls[3871] = {3871 * keV, {{2362 * keV, 100, 1509},}};
    ls[3876] = {3876 * keV, {{1593 * keV, 33, 2282}, {2367 * keV, 100, 1509},}};
    ls[3926] = {3926 * keV, {{1643 * keV, 13.6, 2282}, {2416 * keV, 54.8, 1509}, {3926 * keV, 100, 0},}};
    ls[3944] = {3944 * keV, {{3944 * keV, 100, 0},}};
    ls[3953] = {3953 * keV, {{1340 * keV, 100, 2634},}};
    ls[3963] = {3963 * keV, {{594 * keV, 0, 3368}, {899 * keV, 100, 3063}, {1113 * keV, 55, 2849}, {2453 * keV, 49, 1509},}};
    ls[3964] = {3964 * keV, {{3964 * keV, 100, 0},}};
    // clang-format on
    return ls;
}

PrimaryGeneratorActionScattering::PrimaryGeneratorActionScattering()
    : fAct(BuildLevelScheme(), G4ParticleTable::GetParticleTable()->FindParticle("proton"), 10. * MeV)
{
}

void PrimaryGeneratorActionScattering::GeneratePrimaries(G4Event *event)
{
    fAct.GeneratePrimaryVertex(event);
    //std::cout << event->GetNumberOfPrimaryVertex() << std::endl;
}
