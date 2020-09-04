//Juyoung Park #150155182
//Motorcycle.cpp
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/

#include <iostream>
#include "Motorcycle.h"
#include "Utils.h"
using namespace std;

namespace sdds
{
	Motorcycle::Motorcycle()
	{
		hasSidecar = false;
	}
	Motorcycle::Motorcycle(const char* plate, const char* mnm, bool sidecar) :Vehicle(plate, mnm)
	{
		hasSidecar = sidecar;
	}

	std::istream& Motorcycle::read(std::istream& istr)
	{
		if (isCsv())
		{
			Vehicle::read(istr);
			istr >> hasSidecar;
			istr.ignore();
		}
		else
		{
			cout << endl;
			cout << "Motorcycle information entry" << endl;
			Vehicle::read(istr);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			if (yesOrNo())
			{
				hasSidecar = true;
			}
			else
			{
				hasSidecar = false;
			}
		}
		return istr;
	}
	std::ostream& Motorcycle::write(std::ostream& ostr) const
	{
		if (isEmpty())
		{
			ostr << "Invalid Motorcycle Object" << endl;
		}
		else
		{
			if (isCsv())
			{
				ostr << "M,";
			}
			else
			{
				ostr << "Vehicle type: Motorcycle" << endl;
			}
			Vehicle::write(ostr);
			if (isCsv())
			{
				ostr << hasSidecar << endl;
			}
			else
			{
				if (hasSidecar)
				{
					ostr << "With Sidecar" << endl;
				}
			}
		}
		return ostr;
	}

}

