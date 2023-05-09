Hello, 

You are in the folder 4project. This is a simulation of memory management with address translation, which is usually performed by operating systems. Here are 3 .cpp files, 2 .h and CMakeLists. Also, here is a folder "build" just to skip mkdir part also there are thread1.txt thread2.txt thread3.txt files.
Likewise, there are two tests for your convenience.

First, you should move to the folder "build", then run cmake and make.
Second, run the executable file 2project and specify arguments
Finally, relax and enjoy the output:)

!!please put all thread.txt files in build folder because executable is there!!
!!thread1.txt thread2.txt and thread3.txt are already there!!

if you want to use tests from folder you need to write them like:
../infile1.txt ../outfile1.txt 10
because executable is one folder up (in build)
Or you can just specify full path


Here are the terminal commands:

cd ./build
cmake -S ../
make
./4project ../infile1.txt ../outfile1.txt 10



EXTRA:
Well, it actually works:)
example 2

cd ./build
cmake -S ../
make
./4project ../infile2.dat ../outfile2.txt 10
