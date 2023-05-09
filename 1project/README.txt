cmake -S ./ -B ./build
cmake -S ./test1 -B ./test1
cmake -S ./test2 -B ./test2
cmake -S ./test3 -B ./test3
cmake -S ./test4 -B ./test4
cmake -S ./test5 -B ./test5
make -C ./build
make -C ./test1
make -C ./test2
make -C ./test3
make -C ./test4
make -C ./test5
./build/1project 5

