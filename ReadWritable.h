//Juyoung Park #150155182
//ReadWritable.h
/*I have done all the coding by myself and only copied the code that my professor provided to complete this program.*/

#ifndef _SDDS_READWRITABLE_H
#define _SDDS_READWRITABLE_H

namespace sdds
{
	class ReadWritable
	{
		bool isCsvMode;
	public:
		ReadWritable()
		{
			isCsvMode = false;
		}
		virtual ~ReadWritable()
		{};

		bool isCsv() const;
		virtual void setCsv(bool value);

		virtual std::istream& read(std::istream& istr = std::cin) = 0;
		virtual std::ostream& write(std::ostream& ostr = std::cout) const = 0;
	};

	std::istream& operator>>(std::istream& istr, ReadWritable& rw);
	std::ostream& operator<<(std::ostream& ostr, ReadWritable& rw);


}

#endif