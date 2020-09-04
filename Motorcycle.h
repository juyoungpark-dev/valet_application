//Juyoung Park #150155182
//Motorcycle.h
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/


#ifndef _SDDS_MOTORCYCLE_H
#define _SDDS_MOTORCYCLE_H
#include "Vehicle.h"

namespace sdds
{
	class Motorcycle :public Vehicle
	{
		bool hasSidecar;
	public:
		Motorcycle();
		Motorcycle(const char* plate, const char* mnm, bool sidecar = false);
		Motorcycle(const Motorcycle&) = delete;
		Motorcycle& operator=(const Motorcycle&) = delete;

		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout) const;
	};
}

#endif