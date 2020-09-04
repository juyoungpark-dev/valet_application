//Juyoung Park #150155182
//Car.cpp
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Car.h"
#include "Utils.h"
using namespace std;

namespace sdds
{
	Car::Car()
	{
		carwash = false;
	}
	Car::Car(const char* plate, const char* mnm, bool wash) :Vehicle(plate, mnm)
	{
		carwash = wash;
	}

	istream& Car::read(istream& istr)
	{
		if (isCsv())
		{
			Vehicle::read(istr);
			istr >> carwash;
			istr.ignore();
		}
		else
		{
			cout << endl;
			cout << "Car information entry" << endl;
			Vehicle::read(istr);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			if (yesOrNo())
			{
				carwash = true;
			}
			else
			{
				carwash = false;
			}
		}
		return istr;
	}
	ostream& Car::write(ostream& ostr) const
	{
		if (isEmpty())
		{
			ostr << "Invalid Car Object" << endl;
		}
		else
		{
			if (isCsv())
			{
				ostr << "C,";
			}
			else
			{
				ostr << "Vehicle type: Car" << endl;
			}
			Vehicle::write(ostr);
			if (isCsv())
			{
				ostr << carwash << endl;
			}
			else
			{
				if (carwash)
				{
					ostr << "With Carwash" << endl;
				}
				else
				{
					ostr << "Without Carwash" << endl;
				}
			}
		}
		return ostr;
	}

}