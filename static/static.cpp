#include <cstdint>

extern "C" {

struct delay_gate {
    int32_t active_value;
    int32_t last_value;
    int32_t keep_time;
};

int8_t delay_gate_handler(delay_gate *dg, int32_t delay, int32_t current) {
    int8_t rv = 0;
    if (dg->keep_time >= delay) {
        rv = 1;
        dg->active_value = dg->last_value;
        dg->last_value = current;
        dg->keep_time = 0;
    }

    if (dg->active_value == current) {
        dg->keep_time = 0;
        dg->last_value = current;
    } else if (dg->last_value == current) {
        ++(dg->keep_time);
    } else {
        dg->keep_time = 1;
        dg->last_value = current;
    }

    return rv;
}

};
