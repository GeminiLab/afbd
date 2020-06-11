#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "main_0.h"
#include "../static/static.h"

sim_main_0 s;

int main() {
    memset(&s, 0, sizeof(sim_main_0));

    initialize_sim(&s);

    puts("tick: clk rst cnt");
    puts("=====================");
    for (int i = 0; i < 64; ++i) {
        exec_until(i + 1);
        printf("#%03d: %3d %3d %3d\n", i, s.clk_0, s.rst_0, s.o_0);
    }

    return 0;
}

