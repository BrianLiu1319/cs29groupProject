#pragma once

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Date {
private:
	time_t date;

public:
	Date();
	Date(const Date &) = default;
	Date(time_t);
	void setDate(time_t d) { date = d; }
	friend std::ostream &operator<<(std::ostream &out, const Date &d);
	bool operator<(const Date &d) const;
	bool operator>(const Date &d) const;
	bool operator==(const Date &d) const;
	operator std::string() const;
};
