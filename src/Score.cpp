#include "Score.hpp"

Score::Score() : name(""), date(time(nullptr)), score(0) {}

Score::Score(Date d, unsigned int s) : date(d), score(s) {
	for (int i = 0; i < maxChar; i++) { name[i] = ' '; }
	name[maxChar] = '\0';
}

Score::operator std::string() const {
	std::ostringstream out;
	out << std::left << std::setw(10) << date << " ";
	out << std::left << std::setw(16) << name;
	out << std::right << std::setw(6) << score;
	return out.str();
}

bool Score::operator>(const Score &s) const {
	if (score > s.score) { return true; }
	return false;
}

bool Score::operator<(const Score &s) const {
	if (score < s.score) { return true; }
	return false;
}

bool Score::operator==(const Score &s) const {
	if (score == s.score) { return true; }
	return false;
}

void Score::setName(std::string n) {
	for (int i = 0; i < maxChar; i++) { name[i] = ' '; }
	for (int i = 0; i < maxChar && i < n.size(); i++) { name[i] = n.at(i); }
}
