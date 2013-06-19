#pragma once

#include <SFML\Graphics.hpp>
#include <sstream>
#include <string>

#include "Globals.h"


template<typename T>
class DebugObject : public sf::Text
{
public:
	DebugObject(void) { _dValue = nullptr; };
	~DebugObject(void) {};

	void assignPtr(T dValue, std::string dTitle){
		_dValue = dValue;
		_dTitle = dTitle;
	};

	void update(){
		if (_dValue != 0){
			std::string string = _dTitle;
			std::stringstream ss;
	
			ss << _dValue;

			string += ss.str();

			setString(string);
		}	
	};

private:
	T* _dValue;

	std::string _dTitle;
};