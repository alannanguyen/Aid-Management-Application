// Final Project Milestone 2 - ErrorState Class
// Version 1.0
// ErrorState.cpp
// Date	2018-07-20
// Name Alanna Nguyen
// ID	135129179
// Email anguyen71@myseneca.ca
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
#include "ErrorState.h"
#pragma warning(disable: 4996)

using namespace std;
namespace AMA {
	ErrorState::ErrorState(const char* errorMessage) {
		if (errorMessage == nullptr) {
			_message = nullptr;
		}
		else {
			int size = strlen(errorMessage);
			_message = new char[size + 1];
			strncpy(_message, errorMessage, size);
			_message[size] = '\0';
		}
	}

	ErrorState::~ErrorState() {
		delete[] _message;
		_message = nullptr;
	}

	void ErrorState::clear() {
		delete[] _message;
		_message = nullptr;
	}

	bool ErrorState::isClear() const {
		return _message == nullptr ? true : false;
	}

	void ErrorState::message(const char* str) {
		delete[] _message;
		int size = strlen(str);
		_message = new char[size + 1];
		strncpy(_message, str, size);
		_message[size] = '\0';
	}

	const char* ErrorState::message()const {
		return _message;
	}

	ostream& operator<<(ostream& os, const ErrorState& es) {
		if (!es.isClear()) {
			os << es.message();
			return os;
		}
		else {
			return os;
		}
	}
}