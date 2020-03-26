#include <rtlil/constant.h>


Constant::Constant(int bit, unsigned value): _bit(bit), _value(value) {}

int Constant::bit() const {
    return _bit;
}

unsigned Constant::value() const {
    return _value;
}
