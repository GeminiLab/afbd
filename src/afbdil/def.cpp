#include <afbdil/def.h>

std::string no_slash(std::string& str)
{
	if(str[0] == '\\')
		return str.substr(1);
	return str;
}