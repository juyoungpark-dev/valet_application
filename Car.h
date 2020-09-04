//Juyoung Park #150155182
//Car.h
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/


#ifndef _SDDS_CAR_H
#define _SDDS_CAR_H
#include "Vehicle.h"

namespace sdds
{
	class Car :public Vehicle
	{
		bool carwash;
	public:
		Car();
		Car(const char* plate, const char* mnm, bool wash = false);
		Car(const Car&) = delete;
		Car& operator=(const Car&) = delete;


		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout) const;
	};
}

#endif