/* Citation and Sources...
Filename: Parking.cpp
Author Juyoung Park
150155182
-----------------------------------------------------------
I have done all the coding by myself and only copied the code  that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include "Parking.h"

namespace sdds
{
	Parking::Parking(const char* fileName, int noOfSpots) //Parking constructor
	{
		filename = nullptr;
		num_of_spots = 0;
		parking_spots[0] = nullptr;
		parked_vehicle_num = 0;
		if (fileName != nullptr && fileName[0] != '\0' && noOfSpots >= 10 && noOfSpots <= MAX_PARKING_SPOTS)
		{
			//if valid
			num_of_spots = noOfSpots;
			filename = new char[strlen(fileName) + 1];
			std::strcpy(filename, fileName);
			for (int i = 0; i < num_of_spots;i++)
			{
				parking_spots[i] = nullptr;
			}
			if (loadDataFile())
			{
				//if loaded successfully
				//populate parking menu ----------------
				Menu tempParkingMenu("Parking Menu, select an action:");
				parkingMenu = tempParkingMenu;
				parkingMenu << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Close Parking (End of day)" << "Exit Program";
				//populate vehicle menu ----------------
				Menu tempVehicleMenu("Select type of the vehicle:", 1);
				vehicleSelectionMenu = tempVehicleMenu;
				vehicleSelectionMenu << "Car" << "Motorcycle" << "Cancel";
			}
		}
		else
		{
			std::cout << "Error in data file" << std::endl;
		}
	}
	Parking::~Parking()
	{
		saveDataFile();
		delete[] filename;
		for (int i = 0; i < num_of_spots;i++)
		{
			delete parking_spots[i];
		}
	}
	bool Parking::isEmpty()
	{
		return filename == nullptr;
	}
	void Parking::parkingStatus()
	{
		std::cout << "****** Seneca Valet Parking ******" << std::endl;
		std::cout << "*****  Available spots: ";
		std::cout << std::setw(4) << std::left << num_of_spots - parked_vehicle_num << " *****" << std::endl;
		
	}
	void Parking::parkVehicle()
	{
		Vehicle* v = nullptr;

		
		if (parked_vehicle_num == num_of_spots)
		{
			std::cout << "Parking is full" << std::endl;
		}
		else
		{
			int selection = vehicleSelectionMenu.run();

			if (selection == 3)
			{
				std::cout << "Parking cancelled" << std::endl;
			}
			else if (selection == 1)
			{
				v = new Car();
				park_readNwrite(v);
				v = nullptr;
			}
			else
			{
				v = new Motorcycle();
				park_readNwrite(v);
				v = nullptr;
			}
		}
	}
	void Parking::park_readNwrite(Vehicle* v)
	{
		bool done = false;
		bool canPark = true;
		v->read(std::cin);

		if (parked_vehicle_num > 0)
		{
			for (int i = 0; i < num_of_spots && !done; i++)
			{
				//if the car is already in parkings
				if (parking_spots[i] != nullptr)
				{
					if (*parking_spots[i] == *v)
					{
						std::cout << "Can not park; license plate already in the system!" << std::endl;
						canPark = false;
						done = true;
					}
					done = true;
				}
			}
		}

		done = false;
		if (canPark)
		{
			for (int i = 0;i < num_of_spots && !done;i++)
			{
				if (parking_spots[i] == nullptr)
				{
					parking_spots[i] = v;
					v->setParkingSpot(i + 1);
					parked_vehicle_num++;
					done = true;
				}
			}
			std::cout << std::endl;
			std::cout << "Parking Ticket" << std::endl;
			std::cout << *v;
			std::cout << std::endl;
		}
	}
	void Parking::returnVehicle()
	{
		char tmpLicense[MAX_PLATE + 1];
		int pos;
		bool found = false, done = false;

		//get vehicle's license plate
		std::cout << "Return Vehicle" << std::endl;
		std::cout << "Enter Licence Plate Number: ";
		std::cin.getline(tmpLicense, MAX_PLATE+1, '\n');
		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(2000, '\n');
			std::cout << "Invalid Licence Plate, try again: ";
			std::cin.getline(tmpLicense, MAX_PLATE+1, '\n');
		}

		for (int i = 0;i < parked_vehicle_num && !done;i++)
		{
			if (*parking_spots[i] == tmpLicense)
			{
				pos = i;
				found = true;
				done = true;
			}
		}
		
		std::cout << std::endl;

		if (!found)
		{
			std::cout << "Licence plate " << tmpLicense << " Not found" << std::endl;
		}
		else
		{
			parking_spots[pos]->setCsv(false);
			std::cout << "Returning: " <<std::endl<< *parking_spots[pos];
			delete parking_spots[pos];
			parking_spots[pos] = nullptr;
			parked_vehicle_num--;
			std::cout << std::endl;
		}

	}
	void Parking::listParkedVehicles()
	{
		//go through all the parking_spots[i] (i < num_of_spots)
		//prints all that are not empty
		std::cout << "*** List of parked vehicles ***" << std::endl;
		for (int i = 0; i < num_of_spots;i++)
		{
			if (parking_spots[i] != nullptr)
			{
				parking_spots[i]->setCsv(false);
				std::cout << *parking_spots[i];
				std::cout << "-------------------------------" << std::endl;
			}
		}
	}
	bool Parking::closeParking()
	{
		bool exit = false;
		if (isEmpty())
		{
			std::cout << "Closing Parking" << std::endl;
			exit = true;
		}
		else
		{
			std::cout << "This will Remove and tow all remaining vehicles from the parking!" << std::endl;
			std::cout << "Are you sure? (Y)es/(N)o: ";
			if (!yesOrNo())
			{
				exit = false;
				std::cout << "Aborted!" << std::endl;
			}
			else
			{
				std::cout << "Closing Parking" << std::endl;
				parked_vehicle_num = 0;
				for (int i = 0;i < num_of_spots;i++)
				{
					if (parking_spots[i] != nullptr)
					{
						parking_spots[i]->setCsv(false);
						std::cout << std::endl;
						std::cout << "Towing request" << std::endl;
						std::cout << "*********************" << std::endl;
						std::cout << *parking_spots[i];
						delete parking_spots[i];
						parking_spots[i] = nullptr;
					}
				}
				exit = true;
			}
		}
		return exit;
	}
	bool Parking::exitParkingApp()
	{
		std::string input;
		std::cout << "This will terminate the program!" << std::endl;
		std::cout << "Are you sure? (Y)es/(N)o: ";
		return yesOrNo();
	}
	bool Parking::loadDataFile()
	{
		std::fstream fin;
		fin.open(filename);

		if (!isEmpty())
		{
			if (fin.is_open())
			{
				Vehicle* v = nullptr;
				char cm = '0';
				
				while (fin && parked_vehicle_num < num_of_spots)
				{
					fin.get(cm); fin.ignore();
					if (cm == 'M' ? (v = new Motorcycle()) : (v = new Car()))
					{
						v->setCsv(true);
						if (v->read(fin))
						{
							parking_spots[v->getParkingSpot() - 1] = v;
							parked_vehicle_num++;
						}
						else
						{
							delete v;
						}
					}
				}
				fin.clear();
			}
			else //if the file open is failed
			{
				fin.clear();
			}
		}
		else //if Parking is empty
		{
			fin.clear();
		}
		
		fin.close();

		return fin.good();
	}
	void Parking::saveDataFile()
	{
		std::ofstream fout;
		fout.open(filename);
		if (!isEmpty())
		{
			if (fout.is_open())
			{
				for (int i = 0;i < num_of_spots;i++)
				{
					if (parking_spots[i] != nullptr)
					{
						
						parking_spots[i]->setCsv(true);
						parking_spots[i]->write(fout);
					}
				}

			}
		}
		fout.close();
	}
	int Parking::run()
	{
		int ret =0;
		if (!isEmpty())
		{
			bool exit = false;
			//if Parking is valid
			while (!exit)
			{
				parkingStatus();	//print parking status
				switch (parkingMenu.run())
				{
				case 1:
					parkVehicle();
					break;
				case 2:
					returnVehicle();
					break;
				case 3:
					listParkedVehicles();
					break;
				case 4:
					if (closeParking())
					{
						exit = true;
					}
					break;
				case 5:
					if (exitParkingApp())
					{
						std::cout << "Exiting program!" << std::endl;
						exit = true;
					}
					break;
				}
			}
		}
		else
		{
			ret = 1;
		}
		return ret;
	}

}