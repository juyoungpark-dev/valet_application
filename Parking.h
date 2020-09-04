/* Citation and Sources...
Module: Parking
Filename: Parking.h
Version 1.0
Author Juyoung Park
150155182
-----------------------------------------------------------
I have done all the coding by myself and only copied the code  that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef _SDDS_PARKING_H
#define _SDDS_PARKING_H

#include "Menu.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Utils.h"

namespace sdds
{
	const int MAX_PARKING_SPOTS = 100;

	class Parking
	{
		//properties
		char* filename;
		Menu parkingMenu;
		Menu vehicleSelectionMenu;
		//added properties
		int num_of_spots; //alwyas less than max parking spots
		Vehicle* parking_spots[MAX_PARKING_SPOTS]; //array of pointers
		int parked_vehicle_num; //always less than spot_num

		//private member functions
		bool isEmpty();
		void parkingStatus();
		void parkVehicle();	//displays the submenu
		void returnVehicle();
		void listParkedVehicles();
		bool closeParking();
		bool exitParkingApp();
		bool loadDataFile();
		void saveDataFile();

	public:
		Parking(const char* fileName, int noOfSpots); //constructor
		~Parking(); //destructor
		Parking(const Parking& p) = delete; //copy constructor is denided
		Parking& operator = (const Parking& p) = delete; //copy assignment is denided
		int run();
		void display(std::ostream& os) const;
		void park_readNwrite(Vehicle* v);
	};
}

#endif
