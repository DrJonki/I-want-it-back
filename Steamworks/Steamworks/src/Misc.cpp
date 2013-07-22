#include "Misc.h"

#include <Windows.h>
#include <sstream>


namespace ns{


std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

std::string getString(const int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}
std::string getString(const float value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

} //Namespace ns