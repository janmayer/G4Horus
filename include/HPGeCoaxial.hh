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
	  //Coaxial(std::string DetectorName, G4bool BGO_is_Used, G4double Filter_Dicke);
	  Coaxial(const _spec spec);
  	~Coaxial();

  	G4LogicalVolume* GetLogical() { return HPGeCoaxial_Logical; }
  	G4double GetLength(){ return gesammt_laenge; }

	private:
  	G4LogicalVolume* HPGeCoaxial_Logical;
  	G4double gesammt_laenge;
	};

} //namespace HPGe

#endif //HPGECOAXIAL_HH
