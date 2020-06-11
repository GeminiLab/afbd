./afbd counter.v main
clang++ -c entry.cpp -o entry.o
clang++ entry.o main_0.o -L. -lafbd_static -o main
./main
