#pragma once

#include <rtlil/def.h>

// now bit vector only
class Constant {
	int _bit;
    unsigned _value;

public:
	Constant(int bit, unsigned value);

	int bit() const;
    unsigned value() const;
};

