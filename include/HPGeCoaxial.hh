#ifndef HPGECOAXIAL_HH
#define HPGECOAXIAL_HH

#include "G4LogicalVolume.hh"

namespace HPGe
{
	class Coaxial
	{
	public:
		struct _crystal
		{
			G4double diameter;
			G4double length;
			G4double dead_layer;
			G4double volume;
			G4double hole_diameter;
			G4double hole_length;
		};

		struct _hull
		{
			G4double thickness;
			G4double padding;
			G4double length;
		};

		struct _spec
		{
			std::string name;
			struct _crystal crystal;
			struct _hull hull;
			G4double filter_thickness;
			G4bool bgo;

		};

	public:
		Coaxial(const _spec *spec);
	  	~Coaxial();

  		G4LogicalVolume* GetLogical() { return detector_logical; }
  		G4double GetLength(){ return full_length; }

	private:
  		G4LogicalVolume* detector_logical;
  		G4double full_length;
  		const static G4double MAX_VOLUME_DIFFERENCE;
	};

} //namespace HPGe

#endif //HPGECOAXIAL_HH
