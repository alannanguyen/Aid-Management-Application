#pragma once
// Final Project Milestone 1 - Date Module Header File
// Version 1.0
// Date.h
// Date	2018-07-13
// Author	Alanna Nguyen
// Email	anguyen71@myseneca.ca
// ID		135129179
// Description
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H_
#define AMA_DATE_H_

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace AMA {
	const int min_year = 2000;
	const int max_year = 2030;

	class Date {
		int year;
		int month;
		int day;
		int comparator;
		int error;

		int mdays(int, int) const;
		void errCode(int);

	public:
		Date();
		Date(int, int, int);

		bool isEmpty() const;
		bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
		bool operator<(const Date&) const;
		bool operator>(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>=(const Date&) const;

		int errCode() const;
		bool bad() const;

		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};

	std::ostream& operator<<(std::ostream&, const Date&);
	std::istream& operator>>(std::istream&, Date&);
}
#endif