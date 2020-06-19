#include "DetectorLibrary.hh"

std::map<std::string, HPGe::_spec> BuildSpecs()
{
    std::map<std::string, HPGe::_spec> specs;

    specs["73954"].id = "73954";
    specs["73954"].type = HPGe::HPGeCoaxial;
    specs["73954"].crystal.diameter = 74. * mm;
    specs["73954"].crystal.length = (72. - 2.) * mm;
    specs["73954"].crystal.dead_layer = 2. * mm;
    specs["73954"].crystal.volume = 304. * cm3;
    specs["73954"].crystal.hole_diameter = 5.8 * mm * 2.; // guess
    specs["73954"].crystal.hole_length = 52. * mm; //guess
    specs["73954"].hull.diameter = 80. * mm;
    specs["73954"].hull.padding = 3. * mm;
    specs["73954"].hull.thickness = 1. * mm;
    specs["73954"].hull.endcap_thickness = 1. * mm;
    specs["73954"].hull.length = 16. * cm;
    specs["73954"].check_overlaps = false;

    specs["73959"].id = "73959";
    specs["73959"].type = HPGe::HPGeCoaxial;
    specs["73959"].crystal.diameter = 74. * mm;
    specs["73959"].crystal.length = (72. - 2.) * mm;
    specs["73959"].crystal.dead_layer = 2. * mm;
    specs["73959"].crystal.volume = 306. * cm3;
    specs["73959"].crystal.hole_diameter = 5. * mm * 2.; //guess
    specs["73959"].crystal.hole_length = 46.6 * mm; //guess
    specs["73959"].hull.diameter = 80. * mm;
    specs["73959"].hull.padding = 3. * mm;
    specs["73959"].hull.thickness = 1. * mm;
    specs["73959"].hull.endcap_thickness = 1. * mm;
    specs["73959"].hull.length = 16. * cm;
    specs["73959"].check_overlaps = false;

    specs["elek"].id = "elek";
    specs["elek"].type = HPGe::HPGeCoaxial;
    specs["elek"].crystal.diameter = 60. * mm; //guess
    specs["elek"].crystal.length = (72. - 2.) * mm; //guess
    specs["elek"].crystal.dead_layer = 2. * mm;
    specs["elek"].crystal.volume = 0. * cm3;
    specs["elek"].crystal.hole_diameter = 5. * mm * 2.; //guess
    specs["elek"].crystal.hole_length = 46.6 * mm; //guess
    specs["elek"].hull.diameter = 80. * mm;
    specs["elek"].hull.padding = 3. * mm;
    specs["elek"].hull.thickness = 1. * mm;
    specs["elek"].hull.endcap_thickness = 1. * mm;
    specs["elek"].hull.length = 16. * cm;
    specs["elek"].check_overlaps = false;

    specs["609502"].id = "609502";
    specs["609502"].type = HPGe::HPGeCoaxial;
    specs["609502"].crystal.diameter = 75. * mm; //guess
    specs["609502"].crystal.length = (72. - 1.) * mm; //guess
    specs["609502"].crystal.dead_layer = 2. * mm;
    specs["609502"].crystal.volume = 306. * cm3;
    specs["609502"].crystal.hole_diameter = 5. * mm * 2.; //guess
    specs["609502"].crystal.hole_length = 46.6 * mm; //guess
    specs["609502"].hull.diameter = 80. * mm;
    specs["609502"].hull.padding = 3. * mm;
    specs["609502"].hull.thickness = 1. * mm;
    specs["609502"].hull.endcap_thickness = 1. * mm;
    specs["609502"].hull.length = 16. * cm;
    specs["609502"].check_overlaps = false;

    specs["37N31120A"].id = "37N31120A";
    specs["37N31120A"].type = HPGe::HPGeCoaxial;
    specs["37N31120A"].crystal.diameter = 75. * mm;
    specs["37N31120A"].crystal.length = 92. * mm - 1. * um;
    specs["37N31120A"].crystal.dead_layer = 1. * um;
    specs["37N31120A"].crystal.volume = 400. * cm3;
    specs["37N31120A"].crystal.hole_diameter = 5.8 * mm * 2.; //guess
    specs["37N31120A"].crystal.hole_length = 60. * mm; //guess
    specs["37N31120A"].hull.diameter = 85. * mm;
    specs["37N31120A"].hull.padding = 5. * mm;
    specs["37N31120A"].hull.thickness = 1. * mm;
    specs["37N31120A"].hull.endcap_thickness = 1. * mm;
    specs["37N31120A"].hull.length = 16. * cm;
    specs["37N31120A"].check_overlaps = false;

    specs["25N1546B"].id = "25N1546B";
    specs["25N1546B"].type = HPGe::HPGeCoaxial;
    specs["25N1546B"].crystal.diameter = 55.9 * mm;
    specs["25N1546B"].crystal.length = 55.4 * mm - 1. * um;
    specs["25N1546B"].crystal.dead_layer = 1. * um;
    specs["25N1546B"].crystal.volume = 135. * cm3; //guess
    specs["25N1546B"].crystal.hole_diameter = 3. * mm * 2.; //guess
    specs["25N1546B"].crystal.hole_length = 25. * mm; //guess
    specs["25N1546B"].hull.diameter = 65. * mm;
    specs["25N1546B"].hull.padding = 4. * mm;
    specs["25N1546B"].hull.thickness = 1. * mm;
    specs["25N1546B"].hull.endcap_thickness = 1. * mm;
    specs["25N1546B"].hull.length = 16. * cm;
    specs["25N1546B"].check_overlaps = false;

    specs["miniball_capsule"].id = "miniball_capsule";
    specs["miniball_capsule"].type = HPGe::HPGeHexagonal;
    specs["miniball_capsule"].crystal.diameter = 59. * mm;
    //specs["miniball_capsule"].crystal.diameter   = 55.*mm;
    specs["miniball_capsule"].crystal.length = 78. * mm;
    //specs["miniball_capsule"].crystal.length     = 65.*mm;
    specs["miniball_capsule"].crystal.dead_layer = 0.5 * um;
    //specs["miniball_capsule"].crystal.dead_layer = 2.mm;
    specs["miniball_capsule"].crystal.volume = 0. * g / (5.323 * g / cm3);
    specs["miniball_capsule"].crystal.hole_diameter = 10. * mm;
    specs["miniball_capsule"].crystal.hole_length = specs["miniball_capsule"].crystal.length - 15. * mm;
    specs["miniball_capsule"].hull.diameter = 85. * mm;
    specs["miniball_capsule"].hull.padding = 3. * mm;
    specs["miniball_capsule"].hull.thickness = 1. * mm;
    specs["miniball_capsule"].hull.endcap_thickness = 1. * mm;
    specs["miniball_capsule"].hull.length = 12. * cm;
    specs["miniball_capsule"].check_overlaps = false;
    specs["miniball_capsule"].efficiency = 1.00;

    specs["adjusted_capsule"].id = "adjusted_capsule";
    specs["adjusted_capsule"].type = HPGe::HPGeHexagonal;
    specs["adjusted_capsule"].crystal.diameter = 55. * mm;
    specs["adjusted_capsule"].crystal.length = 65. * mm;
    specs["adjusted_capsule"].crystal.dead_layer = 2 * mm;
    //specs["adjusted_capsule"].crystal.dead_layer = 2.mm;
    specs["adjusted_capsule"].crystal.volume = 0. * g / (5.323 * g / cm3);
    specs["adjusted_capsule"].crystal.hole_diameter = 10. * mm;
    specs["adjusted_capsule"].crystal.hole_length = specs["adjusted_capsule"].crystal.length - 15. * mm;
    specs["adjusted_capsule"].hull.diameter = 85. * mm;
    specs["adjusted_capsule"].hull.padding = 3. * mm;
    specs["adjusted_capsule"].hull.thickness = 1. * mm;
    specs["adjusted_capsule"].hull.endcap_thickness = 1. * mm;
    specs["adjusted_capsule"].hull.length = 12. * cm;
    specs["adjusted_capsule"].check_overlaps = false;

    specs["72341"] = specs["miniball_capsule"];
    specs["72341"].id = "72341";
    specs["72341"].crystal.length = 78. * mm; // from datasheet
    specs["72341"].crystal.volume = 1600. * g / (5.323 * g / cm3); // from datasheet
    specs["72341"].crystal.hole_length = specs["72341"].crystal.length - 15. * mm;

    specs["72397"] = specs["miniball_capsule"];
    specs["72397"].id = "72397";
    specs["72397"].crystal.length = 78.1 * mm; // from datasheet
    specs["72397"].crystal.volume = 1621. * g / (5.323 * g / cm3); // from datasheet
    specs["72397"].crystal.hole_length = specs["72397"].crystal.length - 15. * mm;

    specs["72442"] = specs["miniball_capsule"];
    specs["72442"].id = "72442";
    specs["72442"].crystal.length = 78. * mm; // from datasheet
    specs["72442"].crystal.volume = 1628. * g / (5.323 * g / cm3); // from datasheet
    specs["72442"].crystal.hole_length = specs["72442"].crystal.length - 15. * mm;

    specs["72802"] = specs["miniball_capsule"];
    specs["72802"].id = "72802";
    specs["72802"].crystal.length = 77.9 * mm; // from datasheet
    specs["72802"].crystal.volume = 1585. * g / (5.323 * g / cm3); // from datasheet
    specs["72802"].crystal.hole_length = specs["72802"].crystal.length - 15. * mm;

    specs["72812"] = specs["miniball_capsule"];
    specs["72812"].id = "72812";
    specs["72812"].crystal.length = 78. * mm; // from datasheet
    specs["72812"].crystal.volume = 1587. * g / (5.323 * g / cm3); // from datasheet
    specs["72812"].crystal.hole_length = specs["72812"].crystal.length - 15. * mm;

    specs["72827"] = specs["miniball_capsule"];
    specs["72827"].id = "72827";
    specs["72827"].crystal.length = 78. * mm; // from datasheet
    specs["72827"].crystal.volume = 1596.7 * g / (5.323 * g / cm3); // from datasheet
    specs["72827"].crystal.hole_length = specs["72827"].crystal.length - 15. * mm;

    specs["73211"] = specs["miniball_capsule"];
    specs["73211"].id = "73211";
    specs["73211"].crystal.length = 77.9 * mm; // from datasheet
    specs["73211"].crystal.volume = 1584.7 * g / (5.323 * g / cm3); // from datasheet
    specs["73211"].crystal.hole_length = specs["73211"].crystal.length - 15. * mm;

    specs["CloziA"].id = "CloziA";
    specs["CloziA"].type = HPGe::HPGeClover;
    specs["CloziA"].check_overlaps = true;
    specs["CloziA"].hull.diameter = 2. * 72. * mm;
    specs["CloziA"].hull.thickness = 2.54 * mm;
    specs["CloziA"].hull.endcap_thickness = 1.5 * mm;
    specs["CloziA"].hull.length = 110. * mm; // not measured??
    // specs["CloziA"].hull.diameter = 223. * mm; // from cad hull
    // specs["CloziA"].hull.length = 1015. * mm; // from cad hull

    specs["CloziB"].id = "CloziB";
    specs["CloziB"].type = HPGe::HPGeClover;
    specs["CloziB"].check_overlaps = true;
    specs["CloziB"].hull.diameter = 2. * 72. * mm;
    specs["CloziB"].hull.thickness = 2.54 * mm;
    specs["CloziB"].hull.endcap_thickness = 1.5 * mm;
    specs["CloziB"].hull.length = 110. * mm; // not measured??
    // specs["CloziB"].hull.diameter = 223. * mm; // from cad hull
    // specs["CloziB"].hull.length = 1015. * mm;  // from cad hull

    specs["72890"] = specs["miniball_capsule"];
    specs["72890"].id = "72890";
    specs["72890"].crystal.length = 77.9 * mm; // from datasheet
    specs["72890"].crystal.volume = 1521. * g / (5.323 * g / cm3); // from datasheet
    specs["72890"].crystal.hole_length = specs["72890"].crystal.length - 15. * mm;
    specs["72890"].efficiency = 0.8868;

    specs["72309"] = specs["miniball_capsule"];
    specs["72309"].id = "72309";
    specs["72309"].crystal.length = 76.5 * mm; // from datasheet
    specs["72309"].crystal.volume = 1578. * g / (5.323 * g / cm3); // from datasheet
    specs["72309"].crystal.hole_length = specs["72309"].crystal.length - 15. * mm;
    specs["72309"].efficiency = 0.9132;

    specs["73209"] = specs["miniball_capsule"];
    specs["73209"].id = "73209";
    specs["73209"].crystal.length = 77. * mm; // from datasheet
    specs["73209"].crystal.volume = 1594. * g / (5.323 * g / cm3); // from datasheet
    specs["73209"].crystal.hole_length = specs["73209"].crystal.length - 15. * mm;
    specs["73209"].efficiency = 0.9545;

    specs["72811"] = specs["miniball_capsule"];
    specs["72811"].id = "72811";
    specs["72811"].crystal.length = 78. * mm; // from datasheet
    specs["72811"].crystal.volume = 1590. * g / (5.323 * g / cm3); // from datasheet
    specs["72811"].crystal.hole_length = specs["72811"].crystal.length - 15. * mm;
    specs["72811"].efficiency = 0.8943;

    specs["73002"] = specs["miniball_capsule"];
    specs["73002"].id = "73002";
    specs["73002"].crystal.length = 78.2 * mm; // from datasheet
    specs["73002"].crystal.volume = 1531. * g / (5.323 * g / cm3); // from datasheet
    specs["73002"].crystal.hole_length = specs["73002"].crystal.length - 15. * mm;
    specs["73002"].efficiency = 0.8941;

    return specs;
}
const std::map<std::string, HPGe::_spec> DetectorLibrary::specifications = std::move(BuildSpecs());

Detector *DetectorLibrary::GetDetector(const std::string &id, const std::string &position) const
{
    if (id == "PIPS") {
        return new PIPS(position);
    }

    // Find spec
    auto _s = specifications.find(id);
    if (_s == specifications.end()) {
        G4Exception("DetectorLibrary::GetDetector", "Unknown detector", FatalException, ("HPGe " + id + " has no specification.").c_str());
    }
    const HPGe::_spec spec = _s->second;

    switch (spec.type) {
    case HPGe::HPGeCoaxial:
        return new HPGe::Coaxial(spec, position);
    case HPGe::HPGeHexagonal:
        return new HPGe::Hexagonal(spec, position);
    case HPGe::HPGeClover:
        return new HPGe::Clover(spec, position);
    default:
        G4Exception("DetectorLibrary::GetDetector", "Unknown detector type", FatalException, ("HPGe " + id + " has an unknown type.").c_str());
        return nullptr;
    }
}
