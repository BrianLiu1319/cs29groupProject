#include "Date.hpp"

Date::Date() { date = time(0); }

Date::Date(time_t t) { date = t; }

/***************
Overloaded constructor.
 Accepts date format of yyyy-mm-dd or yyyy/mm/dd
*/
/*
Date::Date(std::string d) {
    std::string yyyy, mm, dd;
    yyyy = d.substr(0, 4);
    mm = d.substr(5, 2);
    dd = d.substr(8, 2);
    date = time(0);
    struct tm * datetime = gmtime(&date);
    datetime->tm_mon = stoi(mm) - 1;
    datetime->tm_mday = stoi(dd);
    datetime->tm_year = stoi(yyyy) - 1900;
    date = timegm(datetime);
}
 */

std::ostream &operator<<(std::ostream &out, const Date &d) {
	// Use the commented code instead if on Windows
	/*
	struct tm  datetime;
	localtime_s(&datetime, &d.date);

	out << std::right << std::setw(2) << std::setfill('0') << datetime.tm_mon + 1 <<
	"/"
	<< std::setw(2) << datetime.tm_mday << "/"
	<< std::setw(4) << (datetime.tm_year + 1900) << std::setw(0) << std::setfill('
	');

	 return out;
	*/


	struct tm *datetime = gmtime(&d.date);

	out << std::right << std::setw(2) << std::setfill('0') << datetime->tm_mon + 1
	    << "/" << std::setw(2) << datetime->tm_mday << "/" << std::setw(4)
	    << (datetime->tm_year + 1900) << std::setw(0) << std::setfill(' ');


	return out;
}

bool Date::operator>(const Date &d) const {
	if (date > d.date) { return true; }
	return false;
}

bool Date::operator<(const Date &d) const {
	if (date < d.date) { return true; }
	return false;
}

bool Date::operator==(const Date &d) const {
	if (date == d.date) { return true; }
	return false;
}

Date::operator std::string() const {
	// Use the commented code instead if on Windows
	/*
	 std::ostringstream temp;

	 struct tm  datetime;
	 localtime_s(&datetime, &date);

	 temp << std::right << std::setw(2) << std::setfill('0') << datetime.tm_mon + 1
	 << "/"
	 << std::setw(2) << datetime.tm_mday << "/"
	 << std::setw(4) << (datetime.tm_year + 1900) << std::setw(0) << std::setfill('
	 ');

	 return temp.str();
	 */


	std::ostringstream temp;
	struct tm *datetime = gmtime(&date);

	temp << std::right << std::setw(2) << std::setfill('0') << datetime->tm_mon + 1
	     << "/" << std::setw(2) << datetime->tm_mday << "/" << std::setw(4)
	     << (datetime->tm_year + 1900) << std::setw(0) << std::setfill(' ');

	return temp.str();
}
