#include "DebugObject.h"


DebugObject::DebugObject(void)
{
	dTime = nullptr;
	dInt = nullptr;
	dFloat = nullptr;
}

DebugObject::~DebugObject(void){}

void DebugObject::assignPtr(sf::Time* time, std::string title)
{
	dTime = time;

	dTitle = title;
}

void DebugObject::assignPtr(int* num, std::string title)
{
	dInt = num;

	dTitle = title;
}

void DebugObject::assignPtr(float* num, std::string title)
{
	dFloat = num;

	dTitle = title;
}

void DebugObject::update()
{
	if (dTime != 0){
		std::string string = dTitle;
		std::ostringstream ss;
	
		ss << (float)dTime->asMicroseconds() / 1000;

		string += ss.str();

		setString(string);
	}

	else if (dInt != 0){
		std::string string = dTitle;
		std::stringstream ss;

		ss << *dInt;

		string += ss.str();

		setString(string);
	}

	else if (dFloat != 0){
		std::string string = dTitle;
		std::stringstream ss;

		ss << *dFloat;

		string += ss.str();

		setString(string);
	}
}