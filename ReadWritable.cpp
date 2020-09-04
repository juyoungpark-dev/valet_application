//Juyoung Park #150155182
//ReadWritable.h
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/

#include <iostream>
#include "ReadWritable.h"
using namespace std;

namespace sdds
{
	bool ReadWritable::isCsv() const
	{
		return isCsvMode;
	}
	void ReadWritable::setCsv(bool value)
	{
		isCsvMode = value;
	}


	std::istream& operator>>(std::istream& istr, ReadWritable& rw)
	{
		rw.read(istr);
		return istr;
	}
	std::ostream& operator<<(std::ostream& ostr, ReadWritable& rw)
	{
		rw.write(ostr);
		return ostr;
	}
}