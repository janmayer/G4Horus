#ifndef G4HORUS_DETECTOR_HH
#define G4HORUS_DETECTOR_HH

#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

class Detector {
  public:
    struct _filter {
        G4String material;
        G4double thickness;
    };

    explicit Detector(const G4String& name, const G4double& length = 0.);
    virtual ~Detector() = default;
    Detector(const Detector&) = delete;
    Detector(Detector&&) = delete;
    Detector& operator=(const Detector&) = delete;
    Detector& operator=(Detector&&) = delete;

    virtual G4LogicalVolume* GetLogical() const
    {
        return fDetectorLV;
    }

    virtual G4double GetLength() const
    {
        return fLength;
    }

    virtual G4String GetName() const
    {
        return fName;
    }

    virtual G4LogicalVolume* BuildFilter(const _filter& filter, const G4double& diameter);

  protected:
    G4LogicalVolume* fDetectorLV;
    G4double fLength;
    G4String fName;
};

#endif //G4HORUS_DETECTOR_HH
