#pragma once
// Final Project - Milestone 3 - MyProduct and Test Modules
// Version 1.0
// Date	2018-08-01
// Product.cpp
// Author	Alanna Nguyen
// ID	135129179
// Email	anguyen71@myseneca.ca
////////////////////////////////////////////////////////////

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include <iostream>
#include "iProduct.h"
#include "ErrorState.h"

namespace AMA {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Product : public iProduct {
		char _type;
		char _sku[max_sku_length + 1];
		char _unit[max_unit_length + 1];
		char * _name;
		int _qtyOnHand;
		int _qtyNeeded;
		double _price;
		bool _taxable;
		ErrorState errorstate;

	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		Product(char = 'N');
		Product(const char*, const char*, const char*, int = 0, bool = true, double = 0.0, int = 0);
		Product(const Product&);
		Product& operator=(const Product&);
		~Product();
		std::fstream&  store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iProduct&) const;
		int operator +=(int);
	};
	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
}

#endif