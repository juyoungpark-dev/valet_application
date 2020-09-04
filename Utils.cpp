//Juyoung Park #150155182
//Utils.cpp
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/

#include <iostream>
#include "Utils.h"
using namespace std;

namespace sdds
{
	bool yesOrNo()
	{
		char answer;
		char input[100];

		cin.getline(input, 100, '\n');
		answer = input[0];
		while (input[1] != '\0' || (answer != 'Y' && answer != 'y' && answer != 'N' && answer !='n'))
		{
			cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			cin.getline(input, 100, '\n');
			answer = input[0];
		}
		return (answer == 'Y' || answer == 'y');
	}

}