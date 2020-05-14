#pragma once

#include "def.h"

#include <iostream>

namespace afbd
{
	class PatternMatching
	{
		std::string _name;
	public:
		PatternMatching(std::string name): _name(name){}
		void reportWarning(std::string str) {std::cout << str << "\n";}
		virtual void match(std::shared_ptr<Module> module) {};
	};
}
