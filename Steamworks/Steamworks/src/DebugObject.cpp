#include "DebugObject.h"

#include <sstream>


DebugObject::DebugObject(void)
{
	_dValuef = nullptr;
	_dValuei = nullptr;
}

DebugObject::~DebugObject(void)
{}

void DebugObject::update()
{
	if (_dValuef != nullptr){
		std::string string = _dTitle;
		std::stringstream ss;
	
		ss << *_dValuef;

		string += ss.str();

		setString(string);
	}
	else if (_dValuei != nullptr){
		std::string string = _dTitle;
		std::stringstream ss;
	
		ss << *_dValuei;

		string += ss.str();

		setString(string);
	}
}