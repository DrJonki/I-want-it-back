#pragma once

#include <string>


namespace ns
{
	std::wstring s2ws(const std::string& s);

	std::string getString(const int value);
	std::string getString(const float value);
}