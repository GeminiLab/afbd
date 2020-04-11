#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "../cmake-build-debug/rtl.h"

sim s;

int main() {
    memset(&s, 0, sizeof(sim));

    puts("# | clk rst out");
    puts("==|============");
    for (int i = 0; i < 32; ++i) {
        s.clk = i & 1;
        s.rst = (i % 23) > 20;

        do_sim(&s);
        printf("%2d|   %1d   %1d %3d\n", i, s.clk, s.rst, s.o);
    }

    return 0;
}
