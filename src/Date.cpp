#include "Date.hpp"

Date::Date() { date = time(nullptr); }

Date::Date(time_t t) { date = t; }

std::ostream &operator<<(std::ostream &out, const Date &d) {
	struct tm *datetime = gmtime(&d.date);

	out << std::right << std::setw(2) << std::setfill('0') << datetime->tm_mon + 1 << "/"
	    << std::setw(2) << datetime->tm_mday << "/" << std::setw(4) << (datetime->tm_year + 1900)
	    << std::setw(0) << std::setfill(' ');

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
	std::ostringstream temp;
	struct tm *datetime = gmtime(&date);

	temp << std::right << std::setw(2) << std::setfill('0') << datetime->tm_mon + 1 << "/"
	     << std::setw(2) << datetime->tm_mday << "/" << std::setw(4) << (datetime->tm_year + 1900)
	     << std::setw(0) << std::setfill(' ');

	return temp.str();
}
