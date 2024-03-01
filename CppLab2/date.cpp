#include "date.h"
#include <string>
#include <iomanip>
#include <cmath>

const int M = 12;	//liczba miesi�cy w roku
const int dl[M] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const std::string months[M] = { "Sty", "Lut", "Mar", "Kwi", "Maj", "Cze", "Lip", "Sie", "Wrz", "Paz", "Lis", "Gru" };


bool Date::ifLeapYear() const {
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

Date::Date(int d, int m, int r, bool format) : day{ d }, month{ m }, year{ r }, format{ format } {}

Date::Date(const char* text, bool format) : format{ format } {
	std::string dateString(text);

	size_t firstDot = dateString.find('.');
	size_t secondDot = dateString.find('.', firstDot + 1);

	day = std::stoi(dateString.substr(0, firstDot));
	month = std::stoi(dateString.substr(firstDot + 1, secondDot - firstDot - 1));
	year = std::stoi(dateString.substr(secondDot + 1));
}

void Date::setFormat(bool format) {
	this->format = format;
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
	if (date.format)
		return out << ' ' << std::setfill('0') << std::setw(2) << date.day << '.' << std::setw(2) << date.month << '.' << date.year;
	return out << ' ' << std::setfill('0') << std::setw(2) << date.day << '.' << std::setw(2) << months[date.month - 1] << '.' << date.year;
}

Date& Date::operator++() {
	if (((*this).ifLeapYear() && month == 2) ? (day == 29) : (day == dl[month - 1])) {
		day = 1;
		if (month == 12) {
			month = 1;
			++year;
		}
		else {
			++month;
		}
	}
	else {
		++day;
	}
	return *this;
}

// Nie chce mi sie robic leapyearow
Date& Date::operator--() {
	if (day == 1) {
		day = dl[month - 2];
		if (month == 1) {
			day = 31;
			month = 12;
			--year;
		}
		else {
			--month;
		}
	}
	else {
		--day;
	}
	return *this;
}

Date& Date::operator+=(int value) {
	if (value == 0) return *this;
	for (int i = 0; i < std::abs(value); i++) {
		if (value > 0) ++(*this);
		else --(*this);
	}
	return *this;
}

bool Date::operator==(const Date& date) const {
	return day == date.day && month == date.month && year == date.year;
}

bool Date::operator<(const Date& date) const {
	if (year == date.year)
		if (month == date.month)
			if (day == date.day)
				return false;
			else
				return day < date.day;
		else
			return month < date.month;
	else
		return year < date.year;
}

int numberOfDays(const Date& d1, const Date& d2) 
{
	Date d1c(d1);
	Date d2c(d2);
	int iterator = 0;

	if (d1c < d2c) {
		while (!(d1c == d2c)) {
			++d1c;
			++iterator;
		}
	}
	else {
		while (!(d1c == d2c)) {
			++d2c;
			++iterator;
		}
	}

	return iterator;
}

Date Date::operator++(int) {
	Date temp{ *this };
	++(*this);
	return temp;
}

