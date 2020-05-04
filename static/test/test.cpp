#include "../static.h"

#include <cstdio>
using namespace std;

struct sim {
    int x;
    int y;
    int z;
};

void x(void *z) {
    auto s = (sim*)z;
    while (true) {
        update(&s->x, now(), 0);
        update(&s->y, now() % 2, 1);
        delay(1);
    }
}

void y(void *z) {
    auto s = (sim*)z;
    while (true) {
        prepare_wait();
        add_wait(1, edge_t::neg);
        do_wait();
        delayed_nonblocking_assign_update(&s->z, s->x * 10 + s->y, 2, 3);
    }
}

int main() {
    sim z;
    z.x = z.y = z.z = 0;
    push_process(x, &z);
    push_process(y, &z);

    for (int i = 0; i < 16; ++i) {
        exec_until(i + 1);
        printf("#%02d: %d %d %d\n", i, z.x, z.y, z.z);
    }
}
