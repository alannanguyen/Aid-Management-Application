#pragma once
// Final Project Milestone 3 - Product Interface
// Version 1.0
// iProduct.h
// 2018/08/02
// Name: Alanna Nguyen
// Email: anguyen71@myseneca.ca
// ID: 135129179
////////////////////////////////////////////////
#ifndef AMA_PERISHABLE_H_
#define AMA_PERISHABLE_H_

#include "Product.h"
#include "Date.h"

namespace AMA {
	class Perishable : public Product {
		Date expire;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};
}

#endif