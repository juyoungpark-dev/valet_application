//Juyoung Park #150155182
//Vehicle.h
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/

#ifndef _SDDS_VEHICLE_H
#define _SDDS_VEHICLE_H
#include "ReadWritable.h"

namespace sdds
{
	const int MAX_PLATE = 8;
	const int MIN_MAKE_MODEL = 2;
	const int MAX_MAKE_MODEL = 60;

	class Vehicle : public ReadWritable
	{
		char licensePlate[MAX_PLATE + 1];
		char* makeNmodel;
		int parkingSpotNum;
	public:
		Vehicle();
		Vehicle(const char* plate, const char* mnm);
		Vehicle(const Vehicle& v) = delete;
		Vehicle& operator=(const Vehicle& v) = delete;
		virtual ~Vehicle();

		int getParkingSpot() const;
		void setParkingSpot(int);
		bool operator==(const char* plate) const;
		bool operator==(const Vehicle& v) const;
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout) const;
	protected:
		void setEmpty();
		bool isEmpty() const;
		const char* getLicensePlate() const;
		const char* getMakeModel() const;
		void setMakeModel(const char*);
	};
}

#endif