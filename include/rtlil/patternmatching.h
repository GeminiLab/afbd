#pragma once

#include <rtlil/def.h>

namespace afbd
{
	class PatternMatching
	{
	public:
		void match(std::shared_ptr<Module> module);
	};
}