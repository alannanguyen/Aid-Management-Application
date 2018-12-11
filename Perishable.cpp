// Final Project Milestone 3 - Product Interface
// Version 1.0
// iProduct.h
// 2018/08/02
// Name: Alanna Nguyen
// Email: anguyen71@myseneca.ca
// ID: 135129179
////////////////////////////////////////////////
#include <iostream>
#include "Perishable.h"

using namespace std;
namespace AMA {

	Perishable::Perishable() : Product::Product('P') {
		expire = Date();
	}
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Product::store(file, false);
		if (file.is_open()) {
			file << ',' << expire;
			if (newLine) {
				file << '\n';
			}
		}
		return file;
	}
	std::fstream& Perishable::load(std::fstream& file) {
		Product::load(file);
		char del;
		if (file.is_open()) {
			file >> del; //single character
				expire.read(file);
		}
		return file;
	}
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Product::write(os, linear);
		if (!isEmpty() || !expire.bad()) {
			if (linear) {
				os << expire;
			}
			else {
				os << "\n Expiry date: " << expire;
			}
		}
		return os;
	}
	std::istream& Perishable::read(std::istream& is) {
		Product::read(is);
		Date temp;
		if (!is.fail()) {
			cout << " Expiry date (YYYY/MM/DD): ";
			temp.read(is);
			if (temp.bad()) {
				if (temp.errCode() == CIN_FAILED) {
					message("Invalid Date Entry");
				}
				else if (temp.errCode() == YEAR_ERROR) {
					message("Invalid Year in Date Entry");
				}
				else if (temp.errCode() == MON_ERROR) {
					message("Invalid Month in Date Entry");
				}
				else if (temp.errCode() == DAY_ERROR) {
					message("Invalid Day in Date Entry");
				}
				is.istream::setstate(std::ios::failbit);
			}
			else {
				expire = temp;
			}
		}
		return is;
	}
	const Date& Perishable::expiry() const {
		return expire;
	}
}