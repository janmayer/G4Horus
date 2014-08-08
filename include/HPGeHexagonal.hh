#ifndef HPGEHEXAGONAL_HH
#define HPGEHEXAGONAL_HH

#include "HPGe.hh"

namespace HPGe
{
	class Hexagonal : public HPGe {
	public:
		Hexagonal(const _spec &spec, const std::string &name, const G4double &filter_thickness);
	  	~Hexagonal();
	};

} //namespace HPGe

#endif //HPGEHEXAGONAL_HH
