class module {
public:
int a;
int b;
int c;
int d;
private:
int now;
int instr0_a_lastvalue;
int instr0_a_newvalue;
int instr0_a_keeptime;
int instr0_b_lastvalue;
int instr0_b_newvalue;
int instr0_b_keeptime;
void do_proc0() {
    bool flag_instr0 = false;
    if (instr0_a_keeptime >= 2) {
        flag_instr0 = true;
        instr0_a_lastvalue = instr0_a_newvalue;
        instr0_a_newvalue = a;
        instr0_a_keeptime = 0;
    }
    if (instr0_b_keeptime >= 2) {
        flag_instr0 = true;
        instr0_b_lastvalue = instr0_b_newvalue;
        instr0_b_newvalue = b;
        instr0_b_keeptime = 0;
    }
    if (flag_instr0) {
        c = instr0_a_lastvalue ^ instr0_b_lastvalue;
    }
    if (instr0_a_lastvalue == a) {
        instr0_a_keeptime = 0;
        instr0_a_newvalue = a;
    } else if (instr0_a_newvalue == a) {
        ++instr0_a_keeptime;
    } else {
        instr0_a_keeptime = 1;
        instr0_a_newvalue = a;
    }
    if (instr0_b_lastvalue == b) {
        instr0_b_keeptime = 0;
        instr0_b_newvalue = b;
    } else if (instr0_b_newvalue == b) {
        ++instr0_b_keeptime;
    } else {
        instr0_b_keeptime = 1;
        instr0_b_newvalue = b;
    }

    d = a ^ b;
}
public:
void do_init() {
    now = 0;
    a = b = c = d = 0;
    instr0_a_lastvalue = instr0_a_newvalue = instr0_a_keeptime = 0;
    instr0_b_lastvalue = instr0_b_newvalue = instr0_b_keeptime = 0;
}
void do_sim() {
    do_proc0();
    ++now;
}
};

#include <cstdio>
using namespace std;

int main() {
    module m;
    int a[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int b[] = { 0, 1, 0, 1, 1, 0, 1, 0, 0, 0 };
    
    m.do_init();
    for (int i = 0; i < 10; ++i) {
        m.a = a[i];
        m.b = b[i];

        m.do_sim();

        printf("%d %d %d %d\n", m.a, m.b, m.c, m.d);
        /*
        printf("## o: %d n: %d k: %d,  o: %d n: %d k: %d\n", 
        m.instr0_a_lastvalue, m.instr0_a_newvalue, m.instr0_a_keeptime,
        m.instr0_b_lastvalue, m.instr0_b_newvalue, m.instr0_b_keeptime);
        */
    }

    return 0;
}
