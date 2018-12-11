// Final Project Milestone 1 - Date Module Implementation File
// Version 1.0
// Date.cpp
// Date	2018-06-22
// Author	Alanna Nguyen
// Email	anguyen71@myseneca.ca
// ID		135129179
// Description
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include "Date.h"

namespace AMA {

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int errorCode) {
		error = errorCode;
	}

	Date::Date() {
		year = 0;
		month = 0;
		day = 0;
		comparator = 0;
		error = NO_ERROR;
	}

	Date::Date(int yr, int mn, int dy) {
		if (yr >= min_year && yr <= max_year) {
			if (mn >= 1 && mn <= 12) {
				if (dy >= 1 && dy <= mdays(mn, yr)) {
					year = yr;
					month = mn;
					day = dy;
					comparator = yr * 372 + mn * 13 + dy;
					error = NO_ERROR;
				}
				else {
					*this = Date();
					error = DAY_ERROR;
				}
			}
			else {
				*this = Date();
				error = MON_ERROR;
			}
		}
		else {
			*this = Date();
			error = YEAR_ERROR;
		}
	}

	bool Date::isEmpty() const {
		return year == 0 && month == 0 && day == 0 && comparator == 0 && error == NO_ERROR ? true : false;
	}

	bool Date::operator==(const Date& rhs) const {
		return (!(isEmpty() && rhs.isEmpty())) && (comparator == rhs.comparator) ? true : false;
	}

	bool Date::operator!=(const Date& rhs) const {
		return (!(isEmpty() && rhs.isEmpty())) && (comparator != rhs.comparator) ? true : false;
	}

	bool Date::operator<(const Date& rhs) const {
		return (!(isEmpty() && !rhs.isEmpty())) && (comparator < rhs.comparator) ? true : false;
	}

	bool Date::operator>(const Date& rhs) const {
		return (!(isEmpty() && !rhs.isEmpty())) && (comparator > rhs.comparator) ? true : false;
	}

	bool Date::operator<=(const Date& rhs) const {
		return (!(isEmpty() && rhs.isEmpty())) && (comparator <= rhs.comparator) ? true : false;
	}

	bool Date::operator>=(const Date& rhs) const {
		return (!(isEmpty() && !rhs.isEmpty())) && (comparator >= rhs.comparator) ? true : false;
	}

	int Date::errCode() const {
		return error;
	}

	bool Date::bad() const {
		return error != NO_ERROR ? true : false;
	}

	std::istream& Date::read(std::istream& istr) {
		int y = 0, m = 0, d = 0;
		char delimiter;

		istr >> y >> delimiter >> m >> delimiter >> d;
		istr.fail();
		if (istr.fail()) {
			error = CIN_FAILED;
		}
		else if (y < min_year || y > max_year) {
			error = YEAR_ERROR;
		}
		else if (m < 1 || m > 12) {
			error = MON_ERROR;
		}
		else if (d < 1 || d > mdays(m, y)) {
			error = DAY_ERROR;
		}
		else {
			error = NO_ERROR;
			year = y;
			month = m;
			day = d;
		}
		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr) const {
		if (isEmpty()) {
			return ostr;
		}
		else {
			ostr << year<< (month < 10 ? "/0" : "/") << month << (day < 10 ? "/0" : "/") << day;
		}
		return ostr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Date& rhs) {
		rhs.write(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Date& rhs) {
		rhs.read(istr);
		return istr;
	}
}