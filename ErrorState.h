#pragma once
// Final Project Milestone 2 - ErrorState Class
// Version 1.0
// ErrorState.h
// Date	2018-07-20
// Name Alanna Nguyen
// ID	135129179
// Email anguyen71@myseneca.ca
/////////////////////////////////////////////////////////////////
#ifndef AMA_ERRORSTATE_H_
#define AMA_ERRORSTATE_H_

namespace AMA {
	class ErrorState {
		char * _message;
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& em) = delete;
		ErrorState& operator=(const ErrorState& em) = delete;
		virtual ~ErrorState();
		void clear();
		bool isClear() const;
		void message(const char*);
		const char* message()const;
	};
	std::ostream& operator<<(std::ostream&, const ErrorState&);
}

#endif
