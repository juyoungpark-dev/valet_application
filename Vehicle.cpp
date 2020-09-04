//Juyoung Park #150155182
//Vehicle.cpp
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Vehicle.h"
using namespace std;

namespace sdds
{
	Vehicle::Vehicle()
	{
		setEmpty();
	}
	Vehicle::Vehicle(const char* plate, const char* mnm)
	{
		setEmpty();
		if (plate != nullptr && mnm != nullptr && plate[0] != '\0' && mnm[0] != '\0')
		{
			size_t plate_len = strlen(plate);
			size_t mnm_len = strlen(mnm);
			if (plate_len <= MAX_PLATE && mnm_len >= MIN_MAKE_MODEL)
			{
				strcpy(licensePlate, plate);
				licensePlate[plate_len] = '\0';

				makeNmodel = new char[mnm_len + 1];
				strcpy(makeNmodel, mnm);

				parkingSpotNum = 0;
			}
		}
	}
	Vehicle::~Vehicle()
	{
		delete[] makeNmodel;
	}


	inline void Vehicle::setEmpty()
	{
		licensePlate[0] = '\0';
		makeNmodel = nullptr;
		parkingSpotNum = -1;
	}
	inline bool Vehicle::isEmpty() const
	{
		return licensePlate[0] == '\0';
	}
	inline const char* Vehicle::getLicensePlate() const
	{
		return this->licensePlate;
	}
	inline const char* Vehicle::getMakeModel() const
	{
		return this->makeNmodel;
	}
	void Vehicle::setMakeModel(const char* mnm)
	{
		size_t mnm_len = strlen(mnm);
		if (makeNmodel != nullptr)
		{
			delete[] makeNmodel;
			makeNmodel = nullptr;
		}

		if (mnm != nullptr && mnm[0] != '\0')
		{
			makeNmodel = new char[mnm_len + 1];
			strcpy(makeNmodel, mnm);
		}
		else
		{
			setEmpty();
		}
	}

	inline int Vehicle::getParkingSpot() const
	{
		return parkingSpotNum;
	}
	void Vehicle::setParkingSpot(int psn)
	{
		if (psn >= 0)
		{
			parkingSpotNum = psn;
		}
		else
		{
			delete[] makeNmodel;
			setEmpty();
		}
	}
	bool Vehicle::operator==(const char* plate) const
	{
		bool equal = true;
		unsigned int m_len = strlen(licensePlate);
		unsigned int p_len = strlen(plate);
		unsigned int cmpLen = m_len > p_len ? m_len : p_len;
		if (plate != nullptr && plate[0] != '\0')
		{
			for (unsigned int i = 0; i < cmpLen && equal; i++)
			{
				if (licensePlate[i] != toupper(plate[i]))
				{
					equal = false;
				}
			}
		}
		return equal;
	}
	bool Vehicle::operator==(const Vehicle& v) const
	{
		return *this == v.getLicensePlate();
	}
	istream& Vehicle::read(istream& istr)
	{

		if (isCsv())
		{
			//read parkingSpotNum
			istr >> parkingSpotNum;
			istr.ignore(); //ignore comma

			//read licensePlate
			char tmpPlate[MAX_PLATE + 1];
			tmpPlate[0] = '\0';
			istr.getline(tmpPlate, MAX_PLATE+1, ',');
			int in = 0;
			for (int i = 0; i < MAX_PLATE && tmpPlate[i] != '\0'; i++)
			{
				licensePlate[i] = toupper(tmpPlate[i]);

				in = i + 1;
			}
			licensePlate[in] = '\0';

			//read make n model
			char tmpMnM[MAX_MAKE_MODEL + 1];
			tmpPlate[0] = '\0';
			istr.getline(tmpMnM, MAX_MAKE_MODEL+1, ',');
			setMakeModel(tmpMnM);
			
		}
		else
		{
			//license plate
			char tmpLicense[MAX_PLATE + 1];
			cout << "Enter Licence Plate Number: ";
			cin.getline(tmpLicense, MAX_PLATE+1, '\n');
			while (cin.fail() || tmpLicense[0] == '\0')
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(2000, '\n');
				}
				cout << "Invalid Licence Plate, try again: ";
				cin.getline(tmpLicense, MAX_PLATE+1, '\n');
			}

			int in = 0;
			for (int i = 0;i < MAX_PLATE && tmpLicense[i] != '\0';i++)
			{
				licensePlate[i] = toupper(tmpLicense[i]);
				in = i + 1;
			}
			licensePlate[in] = '\0';

			//make and model
			cout << "Enter Make and Model: ";
			char* tmpMnM = new char[MAX_MAKE_MODEL + 1];
			istr.getline(tmpMnM, MAX_MAKE_MODEL+1, '\n');
			while (strlen(tmpMnM) < MIN_MAKE_MODEL || strlen(tmpMnM) > MAX_MAKE_MODEL)
			{
				cout << "Invalid Make and model, try again: ";
				delete[] tmpMnM;
				tmpMnM = nullptr;
				tmpMnM = new char[MAX_MAKE_MODEL + 1];
				istr.getline(tmpMnM, MAX_MAKE_MODEL+1, '\n');
			}
			setMakeModel(tmpMnM);
			delete[] tmpMnM;
			tmpMnM = nullptr;
			parkingSpotNum = 0;
		}

		if (istr.fail())
		{
			cin.clear();
			delete[] makeNmodel;
			setEmpty();
		}
		return istr;
	}
	ostream& Vehicle::write(ostream& ostr) const
	{
		if (isEmpty())
		{
			ostr << "Invalid Vehicle Object" << endl;
		}
		else
		{
			if (isCsv())
			{
				ostr << getParkingSpot() << ',' << getLicensePlate() << ',' << getMakeModel() << ',';
			}
			else
			{
				//parking spot
				ostr << "Parking Spot Number: ";
				if (getParkingSpot() == 0)
				{
					ostr << "N/A" << endl;
				}
				else
				{
					ostr << getParkingSpot() << endl;
				}

				//license plate
				ostr << "Licence Plate: " << getLicensePlate() << endl;

				//make and model
				ostr << "Make and Model: " << getMakeModel() << endl;
			}
		}
		return ostr;
	}
}