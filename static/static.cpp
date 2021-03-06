#include "static.h"

#include "3rd/coroutine.h"

#include <map>
#include <set>
#include <queue>
#include <cstdint>
#include <functional>
#include <cstdio>
using namespace std;

#ifdef STATIC_DEBUG
# pragma message("debug activated")
# define debug(str) printf("[%d]" str "\n", coroutine::current())
# define debugf(fmt, ...) printf("[%d]" fmt, coroutine::current(), __VA_ARGS__)
#else
# pragma message("debug disabled")
# define debug(...)
# define debugf(...)
#endif

struct RoutineInDelay {
    tick_t tick;
    coroutine::routine_t routine;
    bool nau;

    bool operator < (const RoutineInDelay &b) const {
        return tick > b.tick;
    }

    RoutineInDelay(tick_t tick, coroutine::routine_t routine, bool nau = false)
        : tick(tick), routine(routine), nau(nau) { }
};

extern "C" {

// all these things are thread_local
thread_local bool _r_very_beginning = true;
thread_local tick_t _r_tick = 0;
thread_local var_id_t _r_var_cnt = 0;

thread_local set<coroutine::routine_t> _r_routines;
thread_local set<coroutine::routine_t> _r_routines_to_delete;
thread_local priority_queue<RoutineInDelay> _r_routines_in_delay;
thread_local set<coroutine::routine_t> _r_curr_events;
thread_local set<coroutine::routine_t> _r_curr_events_inactive;
thread_local set<coroutine::routine_t> _r_curr_events_nau;

// thread_local map<coroutine::routine_t, size_t> _r_success_wait_count;
// thread_local map<var_id_t, map<coroutine::routine_t, size_t>> _r_wait_list_all;
// thread_local map<var_id_t, map<coroutine::routine_t, size_t>> _r_wait_list_pos;
// thread_local map<var_id_t, map<coroutine::routine_t, size_t>> _r_wait_list_neg;
thread_local vector<size_t> _r_success_wait_count;
thread_local map<coroutine::routine_t, size_t> *_r_wait_list_all;
thread_local map<coroutine::routine_t, size_t> *_r_wait_list_pos;
thread_local map<coroutine::routine_t, size_t> *_r_wait_list_neg;

}


void set_var_count(var_id_t count) {
    _r_var_cnt = count;

    delete _r_wait_list_all;
    delete _r_wait_list_pos;
    delete _r_wait_list_neg;

    _r_wait_list_all = new map<coroutine::routine_t, size_t>[_r_var_cnt];
    _r_wait_list_pos = new map<coroutine::routine_t, size_t>[_r_var_cnt];
    _r_wait_list_neg = new map<coroutine::routine_t, size_t>[_r_var_cnt];
}

void push_process(process proc, void *sim) {
    debug("push_process");
    _r_routines.insert(coroutine::create(bind(proc, sim)));
}

void process_end() {
    debug("process_end");
    auto now = coroutine::current();
    _r_routines_to_delete.insert(now);
    coroutine::yield();
}

void exec_until(tick_t t) {
    debug("exec_until");
    if (_r_very_beginning) {
        _r_very_beginning = false;

        for (auto &x: _r_routines) {
            debugf("- begin schedule #%d\n", x);
            coroutine::resume(x);
        }

        for (auto& r: _r_routines_to_delete) {
            _r_routines.erase(r);
            coroutine::destroy(r);
        }
        _r_routines_to_delete.clear();
    }

    while (_r_tick < t) {
        debugf("- now %d\n", _r_tick);
        while (!_r_routines_in_delay.empty() && _r_routines_in_delay.top().tick <= _r_tick) {
            auto top = _r_routines_in_delay.top(); _r_routines_in_delay.pop();
            if (!top.nau) {
                _r_curr_events.insert(top.routine);
            } else {
                _r_curr_events_nau.insert(top.routine);
            }
        }

        executor:
        while (!_r_curr_events.empty()) {
            auto p = _r_curr_events.begin();
            auto routine = *p;
            _r_curr_events.erase(p);
            debugf("- scheduled #%d\n", *p);
            coroutine::resume(routine);
        }

        debug("- active processed");

        if (!_r_curr_events_inactive.empty()) {
            _r_curr_events.insert(_r_curr_events_inactive.begin(), _r_curr_events_inactive.end());
            _r_curr_events_inactive.clear();

            debug("- inactive found and activated");
            goto executor;
        }

        if (!_r_curr_events_nau.empty()) {
            _r_curr_events.insert(_r_curr_events_nau.begin(), _r_curr_events_nau.end());
            _r_curr_events_nau.clear();

            debug("- nau found and activated");
            goto executor;
        }

        for (auto& r: _r_routines_to_delete) {
            _r_routines.erase(r);
            coroutine::destroy(r);
        }
        _r_routines_to_delete.clear();

        if (_r_routines_in_delay.empty() || _r_routines_in_delay.top().tick >= t) {
            _r_tick = t;
            debug("- end reached, exit");
            break;
        } else {
            _r_tick = _r_routines_in_delay.top().tick;
            debugf("- move to %d\n", _r_tick);
        }
    }
}

void reset() {
    debug("reset");
    _r_very_beginning = true;
    _r_tick = 0;

    coroutine::ordinator.coroutine::Ordinator::~Ordinator();
    new (&coroutine::ordinator) coroutine::Ordinator();

    _r_routines.clear();
    _r_routines_to_delete.clear();
    while (!_r_routines_in_delay.empty()) _r_routines_in_delay.pop();

    _r_curr_events.clear();
    _r_curr_events_inactive.clear();
    _r_curr_events_nau.clear();
}


void delay(tick_t span) {
    debugf("delay %d\n", span);
    if (span == 0) {
        _r_curr_events.insert(coroutine::current());
    } else {
        _r_routines_in_delay.push(RoutineInDelay(_r_tick + span, coroutine::current()));
    }
    coroutine::yield();
}

void delay_for_explicit_zero_delay() {
    debug("delay_ezd");
    _r_curr_events_inactive.insert(coroutine::current());
    coroutine::yield();
}

void delay_for_nonblocking_assign_update(tick_t span) {
    debug("delay_nau");
    if (span == 0) {
        _r_curr_events_inactive.insert(coroutine::current());
    } else {
        _r_routines_in_delay.push(RoutineInDelay(_r_tick + span, coroutine::current(), true));
    }
    coroutine::yield();
}

void delayed_nonblocking_assign_update(int32_t *dst, int32_t val, var_id_t v, tick_t span) {
    debug("delayed_nau");
    auto r = coroutine::create([dst, val, v, span](){
        delay_for_nonblocking_assign_update(span);
        update(dst, val, v);
        process_end();
    });

    _r_routines.insert(r);
    _r_curr_events.insert(r);
}

void prepare_wait() {
    debug("prepare_wait");
    if (_r_success_wait_count.size() <= coroutine::current()) {
        _r_success_wait_count.resize(coroutine::current() + 1);
    }
}

map<coroutine::routine_t, size_t>* edge_to_list(edge_t e) {
    return
        e == edge_t::pos ? _r_wait_list_pos :
        e == edge_t::neg ? _r_wait_list_neg :
        _r_wait_list_all;
}

void add_wait(var_id_t v, edge_t e) {
    debug("add_wait");
    auto list = edge_to_list(e);
    list[v][coroutine::current()] = _r_success_wait_count[coroutine::current()];
}

void do_wait() {
    debug("do_wait");
    coroutine::yield();
}

void update(int32_t *dst, int32_t val, var_id_t v) {
    debug("update");
    auto old = *dst;
    if (old != val) {
        *dst = val;
        mark_updated(v, val > old ? edge_t::pos : edge_t::neg);
    }
}

void process_wait_list_item(map<coroutine::routine_t, size_t> &list) {
    for (auto& p: list) {
        if (p.second >= _r_success_wait_count[p.first]) {
            ++_r_success_wait_count[p.first];
            _r_curr_events.insert(p.first);
        }
    }

    list.clear();
}

void mark_updated(var_id_t v, edge_t e) {
    debug("mark_updated");
    process_wait_list_item(_r_wait_list_all[v]);
    process_wait_list_item((e == pos ? _r_wait_list_pos : _r_wait_list_neg)[v]);
}


tick_t now() {
    return _r_tick;
}
