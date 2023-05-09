Hello, 

You are in the folder 3project. Here are 3 .cpp files, 2 .h and CMakeLists. Also, here is a an empty folder "build" just to skip mkdir part and two tests and tests for your convenience.

First, you should move to the folder "build", then run cmake and make.
Second, run the executable file 2project and specify arguments
Finally, relax and enjoy the output:)

if you want to use tests from folder you need to write them like:
../testin2.dat ../out2.txt 10
because executable is one folder up (in build)
Or you can just specify full path


Here are the terminal commands:

cd ./build
cmake -S ../
make
./3project ../testin1.dat ../out1.txt 1



EXTRA:
To add aging you need to go to 3project_lib.h and edit 
"const int AGING     = 0;"
which means no aging to
"const int AGING     = 25;"

and rebuild the project

cd ./build
cmake -S ../
make
./3project ../testin2.dat ../out2.txt 10
