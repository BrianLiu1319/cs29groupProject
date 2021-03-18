#pragma once

#include "Date.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Score {
private:
	static const int maxChar = 16;
	char name[maxChar + 1];
	Date date;
	unsigned int score;

public:
	Score();
	Score(std::string n, Date d, unsigned int s);
	unsigned int getScore() const { return score; }
	Date getDate() const { return date; }
	std::string getName() const {
		std::string s(name);
		return s;
	}
	void setDate(Date d) { date = d; }
	void setDate(time_t d) { date.setDate(d); }
	void setName(std::string n);
	void setScore(unsigned int s) { score = s; }
	operator std::string() const;
	bool operator<(const Score &s) const;
	bool operator>(const Score &s) const;
	bool operator==(const Score &s) const;
};
