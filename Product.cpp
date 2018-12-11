// Final Project - Milestone 3 - MyProduct and Test Modules
// Version 1.0
// Date	2018-08-01
// Product.cpp
// Author	Alanna Nguyen
// ID	135129179
// Email	anguyen71@myseneca.ca
////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Product.h"
#include "ErrorState.h"
#pragma warning(disable : 4996)

using namespace std;
namespace AMA {
	void Product::name(const char* name_) {
		if (name_ != nullptr) {
			_name = new char[max_name_length + 1];
			strncpy(_name, name_, max_name_length);
			_name[max_name_length] = '\0';
		}
		else {
			delete[] _name;
			_name = nullptr;
		}
	}
	const char* Product::name() const {
		return _name == nullptr ? nullptr : _name;
	}
	const char* Product::sku() const {
		return _sku;
	}
	const char* Product::unit() const {
		return _unit;
	}
	bool Product::taxed() const {
		return _taxable;
	}
	double Product::price() const {
		return _price;
	}
	double Product::cost() const {
		if (_taxable) {
			double hst = _price * tax_rate;
			return _price + hst;
		}
		else {
			return _price;
		}
	}
	void Product::message(const char* str) {
		errorstate.message(str);
	}
	bool Product::isClear() const {
		return errorstate.isClear() ? true : false;
	}

	Product::Product(char type_) {
		_type = type_;
		_sku[0] = '\0';
		_unit[0] = '\0';
		_name = nullptr;
		_qtyOnHand = 0;
		_qtyNeeded = 0;
		_price = 0.0;
		_taxable = false;
	}
	Product::Product(const char* sku_, const char* name_, const char* unit_, 
		int qtyOnHand_, bool taxable_, double price_, int qtyNeeded_) {
		strncpy(_sku, sku_, max_sku_length);
		_sku[max_sku_length] = '\0';
		name(name_);
		strncpy(_unit, unit_, max_unit_length);
		_unit[max_unit_length] = '\0';
		_qtyOnHand = qtyOnHand_;
		_taxable = taxable_;
		_price = price_;
		_qtyNeeded = qtyNeeded_;
	}
	Product::Product(const Product& src) {
		_type = src._type;
		_qtyOnHand = src._qtyOnHand;
		_qtyNeeded = src._qtyNeeded;
		_price = src._price;
		_taxable = src._taxable;
		strncpy(_sku, src._sku, max_sku_length);
		_sku[max_sku_length] = '\0';
		strncpy(_unit, src._unit, max_unit_length);
		_unit[max_unit_length] = '\0';
		name(src._name);
	}
	Product& Product::operator=(const Product& src) {
		if (this != &src) {
			_type = src._type;
			_qtyOnHand = src._qtyOnHand;
			_qtyNeeded = src._qtyNeeded;
			_price = src._price;
			_taxable = src._taxable;
			strncpy(_sku, src._sku, max_sku_length);
			_sku[max_sku_length] = '\0';
			strncpy(_unit, src._unit, max_unit_length);
			_unit[max_unit_length] = '\0';
			delete[] _name;
			name(src._name);
		}
		return *this;
	}
	Product::~Product() {
		delete[] _name;
		_name = nullptr;
	}
	std::fstream&  Product::store(std::fstream& file, bool newLine) const {
		char del = ',';
		if (file.is_open()) {
			file << _type << del 
				<< _sku << del 
				<< _name << del 
				<< _unit << del
				<< _taxable << del 
				<< _price << del 
				<< _qtyOnHand << del 
				<<_qtyNeeded;
			if (newLine) {
				file << endl;
			}
		}
		return file;
	}
	std::fstream& Product::load(std::fstream& file) {
		char skp[max_sku_length + 1];
		char uni[max_unit_length + 1];
		char nom[max_name_length + 1];
		int qtyOH;
		int qtyN;
		double pri;
		bool tax;
		char del;
		if (file.is_open()) {
			file.getline(skp, max_sku_length, ',');
			file.getline(nom, max_name_length, ',');
			file.getline(uni, max_unit_length, ',');
			file >> tax >> del;
			file >> pri >> del;
			file >> qtyOH >> del;
			file >> qtyN;
		}
		Product temp(skp, nom, uni, qtyOH, tax, pri, qtyN);
		*this = temp;
		return file;
	}
	std::ostream& Product::write(std::ostream& os, bool linear) const {
		if (!isClear()) {
			os << errorstate.message();
			return os;
		}
		char del = '|';
		if (linear) {
			os << fixed << left << setw(max_sku_length) << _sku << del
				<< setw(20) << _name << del << right
				<< setw(7) << setprecision(2) << cost() << del
				<< setw(4) << _qtyOnHand << del << left
				<< setw(10) << _unit << del << right
				<< setw(4) << _qtyNeeded << del;
		}
		else {
			os << " Sku: " << _sku << endl;
			os << " Name (no spaces): " << _name << endl;
			os << " Price: " << _price << endl;
			os << " Price after tax: ";
			if (_taxable) {
				os << cost() << endl;
			}
			else {
				os << "N/A" << endl;
			}
			os << " Quantity on Hand: " << _qtyOnHand << ' ' << _unit << endl;
			os << " Quantity needed: " << _qtyNeeded;
		}
		return os;
	}
	std::istream& Product::read(std::istream& is) {
		errorstate.clear();
		Product temp;
		temp._name = new char[max_name_length + 1];
		char h;

		cout << " Sku: ";
		is >> temp._sku;
		cout << " Name (no spaces): ";
		is >> temp._name;
		cout << " Unit: ";
		is >> temp._unit;
		cout << " Taxed? (y/n): ";
		is >> h;
		if (h == 'Y' || h == 'y') {
			temp._taxable = true;
		}
		else if (h == 'N' || h == 'n') {
			temp._taxable = false;
		}
		else {
			message("Only (Y)es or (N)o are acceptable");
			is.setstate(std::ios::failbit);
			return is;
		}
		cout << " Price: ";
		is >> temp._price;
		if (is.fail()) {
			message("Invalid Price Entry");
			return is;
		}
		cout << " Quantity on hand: ";
		is >> temp._qtyOnHand;
		if (is.fail()) {
			message("Invalid Quantity Entry");
			return is;
		}
		cout << " Quantity needed: ";
		is >> temp._qtyNeeded;
		if (is.fail()) {
			message("Invalid Quantity Needed Entry");
			return is;
		}
		is.ignore();
		if (isClear()) {
			_qtyOnHand = temp._qtyOnHand;
			_qtyNeeded = temp._qtyNeeded;
			_price = temp._price;
			_taxable = temp._taxable;
			strncpy(_sku, temp._sku, max_sku_length);
			_sku[max_sku_length] = '\0';
			strncpy(_unit, temp._unit, max_unit_length);
			_unit[max_unit_length] = '\0';
			name(temp._name);
		}
		delete[] temp._name;
		temp._name = nullptr;
		return is;
	}
	bool Product::operator==(const char* str) const {
		return strcmp(str, _sku) == 0 ? true : false;
	}
	double Product::total_cost() const {
		return cost() * _qtyOnHand;
	}
	void Product::quantity(int qtyOnHand_) {
		_qtyOnHand = qtyOnHand_;
	}
	bool Product::isEmpty() const {
		return (_sku[0] == '\0' && _unit[0] == '\0' &&
			_name == nullptr && _taxable == false && _qtyOnHand == 0 &&
			_qtyNeeded == 0 && _price == 0.0) ? true : false;
	}
	int Product::qtyNeeded() const {
		return _qtyNeeded;
	}
	int Product::quantity() const {
		return _qtyOnHand;
	}
	bool Product::operator>(const char* sku_) const {
		return strcmp(_sku, sku_) == 1 ? true : false;
	}
	bool Product::operator>(const iProduct& obj) const {
		return strcmp(_name, obj.name()) == 1 ? true : false;
	}
	int Product::operator+=(int qty) {
		if (qty > 0) {
			_qtyOnHand += qty;
		}
		return _qtyOnHand;
	}
	ostream& operator<<(ostream& os, const iProduct& obj) {
		obj.write(os, true);
		return os;
	}
	istream& operator>>(istream& is, iProduct& obj) {
		obj.read(is);
		return is;
	}
	double operator+=(double& value, const iProduct& obj) {
		double total = value + obj.total_cost();
		return total;
	}
}