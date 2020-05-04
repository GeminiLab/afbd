#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "cmake-build-debug/rtl.h"
#include "static/static.h"

sim_counter s;

int main() {
    memset(&s, 0, sizeof(sim_counter));

    initialize_sim(&s);

    for (int i = 0; i < 16; ++i) {
        exec_until(i + 1);
        printf("#%03d: %1d %1d %03d\n", i, s.clk, s.rst, s.o);
    }

    return 0;
}

/*
printf("## o: %d n: %d k: %d\n",
       s.dg_5.o, s.dg_5.n, s.dg_5.k);
printf("## o: %d n: %d k: %d\n",
       s.dg_6.o, s.dg_6.n, s.dg_7.k);
printf("## o: %d n: %d k: %d\n",
       s.dg_7.o, s.dg_7.n, s.dg_7.k);
       */