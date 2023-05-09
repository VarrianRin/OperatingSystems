#include "4project_lib.h"

int       Nprocs        = 0;
int       Nframes       = 0;
int       SizeRAM       = 0;
int       SizeFrame     = 0;
int*      RAM           = nullptr;
FILE*     OUTPUT        = nullptr;

sem_t OutSem;
sem_t MemSem;

procType*       proc;
PagePlaceType   PagePlace = {};

int main(int argc, const char* argv[]) {

    const char* InputFile  = argv[1]; //"..\\infile1.txt";
    const char* OutputFile = argv[2]; //"..\\outfile1.txt";
    int         seed       = atoi(argv[3]);

    OUTPUT = fopen(OutputFile, "w");

    TextParser(InputFile);
    RAM = InitRAM(seed);
    InitProcs();

    sem_init(&OutSem, 0, 1);
    sem_init(&MemSem, 0, 1);
    pthread_t p[Nprocs];
    tinfo_t t[Nprocs];

    int i = 0;
    for ( ; i < Nprocs; i++) {
        t[i].thread_id = i;
        Pthread_create(&p[i], NULL, ExecuteProc, &t[i]);
    }

    for (i = 0; i < Nprocs; i++) {
        Pthread_join(p[i], NULL);
    }
    fprintf(OUTPUT, "Main: program completed\n");

    for(i = 0; i < Nprocs; i++) {
        free(proc[i].access);
        free(proc[i].PageTable);
    }
    free(proc);
    free(PagePlace.frame);
    free(RAM);
    ListKill(&PagePlace.Clock);
    fclose(OUTPUT);

    return 0;
}