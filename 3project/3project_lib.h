/*#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>*/
#include "mylist.h"

enum proc_status {ABSENT, QUEUE, RUNNING, WAITING, FINISHING, FINISHED, PREEMPTED, LOADING, IO};
enum output_phrase {Loading, Running, Finishing, FinishingLoading, Preempted};
enum alg_indexes {FCFS, SJF, STCF, RoundRobin, Priority};
const int MAXQUEUE  = 10000;
const int Nal       = 5;
const int AGING     = 25;


struct proc {

    int         index;
    int         initburst;
    int         burst;
    int         priority;
    int         arrival;
    int         TT_time;
    int         WT_time;
    int         RRblocks;
    proc_status status;  //0 - hasn't arrived; 1 - waiting in queue; 2 - executing; 3 - waiting; 4 - finished
};

struct algorithm {

    alg_indexes index;
    int         running;
    const char* name;
    proc*       procs;
    List*       schedule;
    List*       sequence;
    List*       IOqueue;
    double      WT_time;
    double      TT_time;
    int         Nswitches;
    int         RRquant;
};

struct time_elem {

    int  n_proc;
    int* ArrivalProc;
};

struct write_pattern {

    output_phrase phrase;
    int           first;
    int           second;
    int           third;
    int           forth;
    char*         queue;

};


int WriteProcs(struct proc* procs, int Nprocs);

int WriteIncome(struct time_elem* income, int AllTime);

int LineCounter(const char* text);

char* WinReader (const char* FileName, int* SizeFile);

int ProcParser (char* text, int SizeFile, struct proc* procs, int* AllTime);

struct proc* TextParser(const char* FileName, int* Nprocs, int* AllTime);

time_elem* ProcIncome(struct proc* procs, int Nprocs, int AllTime);

int AssignProc(proc* procs, algorithm* als, int Nprocs);

int ComparePriority(const void* a, const void* b);

int CompareBurst(const void* a, const void* b);

int SortSchedule(algorithm* Al);

int ProcCheck(proc* procs, algorithm* Al, int Nprocs);

char* WriteQueue(List* schedule);

int WriteLoading(write_pattern* pattern, FILE* Output);

int WriteRunning(write_pattern* pattern, FILE* Output);

int WriteFinishingLoading(write_pattern* pattern, FILE* Output);

int WriteFinishing(write_pattern* pattern, FILE* Output);

int WritePreempted(write_pattern* pattern, FILE* Output);

output_phrase ProcessesSituation(algorithm* Al, int* pc, int Nprocs, int* place, int tc, FILE* Output);

output_phrase Process(algorithm* Al, int* pc, int Nprocs, int tc, FILE* Output = nullptr);

int OneClock(time_elem income, algorithm* Al, int tc, int period, int* pc, int Nprocs, FILE* Output);

int AlgFinish(algorithm* als, int Nprocs, FILE* Output);

void AlsInit(algorithm* als, proc* procs, int Nprocs, FILE* Output);

int CompareWT(const void* a, const void* b);

int CompareTT(const void* a, const void* b);

int CompareNswitches(const void* a, const void* b);

void OverallSummary(algorithm* als, FILE* Output);

