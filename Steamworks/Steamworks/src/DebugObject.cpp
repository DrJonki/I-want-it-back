#include "DebugObject.h"

DebugObject::DebugObject(void)
{
	_dValuef = nullptr;
	_dValuei = nullptr;
}

DebugObject::~DebugObject(void)
{}

void DebugObject::update()
{
	if (_dValuef != 0){
		std::string string = _dTitle;
		std::stringstream ss;
	
		ss << *_dValuef;

		string += ss.str();

		setString(string);
	}
	else if (_dValuei != 0){
		std::string string = _dTitle;
		std::stringstream ss;
	
		ss << *_dValuei;

		string += ss.str();

		setString(string);
	}
}