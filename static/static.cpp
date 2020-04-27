#include <cstdint>
#include <queue>
#include <cstdio>

extern "C" {

typedef void *eq;
typedef void *event;
typedef void *sim;
typedef int32_t tick_t;

void push_active(eq q, tick_t t, event e);
void push_inactive(eq q, tick_t t, event e);
void push_nau(eq q, tick_t t, event e);

void active_inactive(eq q);
void active_nau(eq q);

eq new_eq();
void exec_until(eq q, sim s, tick_t *t, tick_t till);

};


using namespace std;

// implement
enum EventType {
    Active = 0,
    Inactive = 1,
    Nau = 2,
};

struct EventInQueue {
    event e;
    tick_t tick;
    EventType type;

    EventInQueue(event e, tick_t tick, EventType type)
        : e(e), tick(tick), type(type) { }
};

struct EventInQueueComp {
    bool operator()(const EventInQueue a, const EventInQueue b) const {
        return a.tick != b.tick ? a.tick > b.tick : a.type > b.type;
    }
};

struct EqImpl {
    priority_queue<EventInQueue, vector<EventInQueue>, EventInQueueComp> q;
    queue<EventInQueue> active;
    queue<EventInQueue> inactive;
    queue<EventInQueue> nau;

    tick_t now;

    public:
    EqImpl()
        : q(), active(), inactive(), nau(), now(-1) { }
};

typedef void (*EventImpl)(eq, sim, tick_t);

#define eq_impl(v) ((EqImpl*)v)
#define event_impl(v) ((EventImpl)v)

void push_active(eq q, tick_t t, event e) {
    auto qi = eq_impl(q);
    if (t < qi->now) {
        return;
    } else if (t == qi->now) {
        qi->active.push(EventInQueue(e, t, EventType::Active));
    } else {
        qi->q.push(EventInQueue(e, t, EventType::Active));
    }
}

void push_inactive(eq q, tick_t t, event e) {
    auto qi = eq_impl(q);
    if (t < qi->now) {
        return;
    } else if (t == qi->now) {
        qi->inactive.push(EventInQueue(e, t, EventType::Inactive));
    } else {
        qi->q.push(EventInQueue(e, t, EventType::Inactive));
    }
}

void push_nau(eq q, tick_t t, event e) {
    auto qi = eq_impl(q);
    if (t < qi->now) {
        return;
    } else if (t == qi->now) {
        qi->nau.push(EventInQueue(e, t, EventType::Nau));
    } else {
        qi->q.push(EventInQueue(e, t, EventType::Nau));
    }
}

void active_inactive(eq q) {
    auto qi = eq_impl(q);
    while (!qi->inactive.empty()) {
        qi->active.push(qi->inactive.front());
        qi->inactive.pop();
    }

}

void active_nau(eq q) {
    auto qi = eq_impl(q);
    while (!qi->nau.empty()) {
        qi->active.push(qi->nau.front());
        qi->nau.pop();
    }
}

eq new_eq() {
    return new EqImpl();
}

void exec_until(eq q, sim s, tick_t *t, tick_t till) {
    auto qi = eq_impl(q);
    auto queue = &qi->q;
    auto active = &qi->active;
    auto inactive = &qi->inactive;
    auto nau = &qi->nau;
    qi->now = *t; 

    while (true) {
        if (*t >= till || queue->empty()) {
            qi->now = *t = till;
            break;
        }

        while (!queue->empty() && queue->top().tick == *t) {
            auto e = queue->top(); queue->pop();
            if (e.type == EventType::Active) {
                active->push(e);
            } else if (e.type == EventType::Inactive) {
                inactive->push(e);
            } else if (e.type == EventType::Nau) {
                nau->push(e);
            } 
        }

        while (true) {
            while (!active->empty()) {
                auto e = active->front(); active->pop();
                event_impl(e.e)(q, s, *t);
            }

            if (!inactive->empty()) {
                active_inactive(q);
            } else if (!nau->empty()) {
                active_nau(q);
            } else {
                break;
            }
        }

        if (queue->empty()) {
            qi->now = *t = *t + 1;
            break;
        } else {
            auto next = queue->top().tick;
            qi->now = *t = next;
            if (next >= till) break;
        }
    }
}



void xx(eq q, sim x, tick_t t) {
    *((int*)x) = 1 - *((int*)x);
    push_active(q, t + 1, (event)xx);
}

void yy(eq q, sim x, tick_t t) {
    *((int*)x) = 1;
    push_nau(q, t + 3, (event)yy);
}


int main() {
    auto ei = new_eq();
    int v = 1;

    push_active(ei, 0, (event)xx);
    push_nau(ei, 0, (event)yy);

    for (int i = 0; i < 16; ) {
        int oi = i;
        exec_until(ei, &v, &i, i + 1);

        printf("@%d: %d\n", oi, v);
    }

    return 0;
}
