#ifndef Date_hpp
#define Date_hpp

#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class Date {
    time_t date;
public:
    Date();
    Date(const Date&) = default;
    Date(time_t);
    //Date(std::string d);
    void setDate(time_t d) { date = d; }
    friend std::ostream & operator << (std::ostream &out, const Date &d);
    bool operator < (const Date& d) const;
    bool operator > (const Date& d) const;
    bool operator == (const Date& d) const;
    operator std::string() const;
};

#endif /* Date_hpp */
