# How to use it

## Pre-compilng

Install following packages first:

```sh
sudo apt install llvm-dev-8 llvm-dev
```

## Compiling

Compiling this project is as simple as compiling any other CMake project. Just run:

```sh
cmake .
make
```

If you want to build this project in a subdirectory, which is suggested by CMake and me, run:

```sh
mkdir build
cd build
cmake ..
make
```

What you need are `afbd` and `libafbd_static.a`, as well as `static\static.h`.

## Usage

> See directory `./eg` for an example. Execute:
>
> ```sh
> cd eg
> ./build.sh
> ./run.sh
> ```

To simulate a verilog source file, first run:

```sh
./afbd <path-of-verilog> <name-of-top-module>
```

You will get an object code file named `<name-of-top-module>_0.o` and a header file named `<name-of-top-module>_0`.h. Then you should write an entry cpp source file, like:

```c++
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

    exec_until(i + 1);
    printf("%3d %3d %3d\n", s.clk_0, s.rst_0, s.o_0);

    return 0;
}
```

Compile this source file and link it with `<name-of-top-module>_0.o` and `libafbd_static.a`, you can get the simulation executable binary.
