#ifndef __common_threads_h__
#define __common_threads_h__

#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include "mylist.h"

#ifdef __linux__
#include <semaphore.h>
#endif

#define Pthread_create(thread, attr, start_routine, arg) assert(pthread_create(thread, attr, start_routine, arg) == 0);
#define Pthread_join(thread, value_ptr)                  assert(pthread_join(thread, value_ptr) == 0);

#define Pthread_mutex_init(m, v)                         assert(pthread_mutex_init(m, v) == 0);
#define Pthread_mutex_lock(m)                            assert(pthread_mutex_lock(m) == 0);
#define Pthread_mutex_unlock(m)                          assert(pthread_mutex_unlock(m) == 0);

#define Pthread_cond_init(cond, v)                       assert(pthread_cond_init(cond, v) == 0);
#define Pthread_cond_signal(cond)                        assert(pthread_cond_signal(cond) == 0);
#define Pthread_cond_wait(cond, mutex)                   assert(pthread_cond_wait(cond, mutex) == 0);

#define Mutex_init(m)                                    assert(pthread_mutex_init(m, NULL) == 0);
#define Mutex_lock(m)                                    assert(pthread_mutex_lock(m) == 0);
#define Mutex_unlock(m)                                  assert(pthread_mutex_unlock(m) == 0);

#define Cond_init(cond)                                  assert(pthread_cond_init(cond, NULL) == 0);
#define Cond_signal(cond)                                assert(pthread_cond_signal(cond) == 0);
#define Cond_wait(cond, mutex)                           assert(pthread_cond_wait(cond, mutex) == 0);

#ifdef __linux__
#define Sem_init(sem, value)                             assert(sem_init(sem, 0, value) == 0);
#define Sem_wait(sem)                                    assert(sem_wait(sem) == 0);
#define Sem_post(sem)                                    assert(sem_post(sem) == 0);
#endif // __linux__

#endif // __common_threads_h__


const int Nregisters    = 32;
const int NAME_SIZE     = 32;
struct transl {

    int         procs;
    bool        valid;
    int         min_adress;
    int         max_adress;
    int         idx_page;
    int         idx_frame;
};
struct procType {

    long int*   access;
    transl*     PageTable;
    int         index;
    int         current_access;
    int         TableSize;
    int         max_access;
    int         VirtualSize;
    int         Registers[Nregisters] = {};
    char        FileName[NAME_SIZE]   = {};

};
struct FrameType{
    transl*     FrameOwner;
    bool        ref;
    int         min_adress;
    int         max_adress;
};
struct PagePlaceType {

    List        Clock;
    FrameType*  frame;
    Element*    CurrentPlace;
};
typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

int LineCounter(const char* text);

char* WinReader (const char* FileName, int* SizeFile);

int ProcParser (char* text, int idx, int Nlines);

int InputParser (char* text);

int TextParser(const char* FileName, bool PROC_PARS = false, int idx = 0);

int* InitRAM(int seed);

int InitProcs();

int Translate(int id, int VA, int page, int frame, bool old = true);

int FindPlace(int id, int VA, transl* translation);

int MemAccess(int id, int adress, int value = POISON);

void* ExecuteProc(void *arg);
