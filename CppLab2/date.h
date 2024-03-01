#pragma once
#include <iostream>

class Date {
	int day;
	int month;
	int year;

	bool format;

private:
	bool ifLeapYear() const;

public:
	Date(int d = 1, int m = 3, int r = 2024, bool format = false);
	Date(const char* text, bool format = false);

	//uzupe�nij TYLKO POTRZEBNE metody i funkcje zaprzyja�nione
	void setFormat(bool format);

	Date& operator++();
	Date& operator--();
	Date& operator+=(int value);
	bool operator==(const Date& date) const;
	bool operator<(const Date& date) const;

	friend std::ostream& operator<<(std::ostream& out, const Date& date);
};

int numberOfDays(const Date& d1, const Date& d2);
