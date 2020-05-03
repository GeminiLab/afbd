#pragma once

#include <cstdint>

typedef void (*process)(void*);
typedef int32_t tick_t;
typedef int32_t var_id_t;

enum edge_t {
    neg = -1,
    all = 0,
    pos = 1,
};

extern "C" {

// all these things are thread_local
void push_process(process proc, void *sim);
void process_end();
void exec_until(tick_t t);
void reset();

void delay(tick_t span);
void delay_for_explicit_zero_delay();
void delay_for_nonblocking_assign_update(tick_t span);
void delayed_nonblocking_assign_update(int32_t *dst, int32_t val, tick_t span);
void prepare_wait();
void add_wait(var_id_t v, edge_t e);
void do_wait();

void update(int32_t *dst, int32_t val, var_id_t v);
void mark_updated(var_id_t v, edge_t e);

tick_t now();

}
