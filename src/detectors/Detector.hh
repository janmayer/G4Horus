#pragma once

#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4Transform3D.hh"
#include <string>

class Detector {
  public:
    explicit Detector(std::string name, const G4double& length = 0.);
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

    virtual G4double GetOffset() const
    {
        return fLength / 2.;
    }

    virtual G4double GetWidth() const
    {
        return fWidth;
    }

    virtual std::string GetName() const
    {
        return fName;
    }

  protected:
    G4LogicalVolume* fDetectorLV;
    G4double fLength;
    G4double fWidth;
    std::string fName;
};
