#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef int Elem_t;

const Elem_t    POISON         = -1073676287;
const int       INITSIZE       = 20,
                INCREASECOEFF  = 2,
                N_ERRORS       = 5,
                SIZE_ERROR     = 1,
                FREE_ERROR     = 2,
                TAIL_ERROR     = 3,
                HEAD_ERROR     = 4,
                DATA_ERROR     = 5,
                NULL_POINT     = 6;

#define CHECKLIST(list) //if(ListOk(list)) ListDump(list, __FILE__, __LINE__, __PRETTY_FUNCTION__);

struct Element {

    Elem_t   data;
    int      next;
    int      prev;
};

struct List {

    Element* Elem;
    int      head;
    int      tail;
    int      free;
    int      size;
    int      errcode;
};

int ListOk(List* list);

bool ErrorPrint(int errcode);

bool DotWriter(const List* list);

bool ListDump(const List* list, const char* file, int line, const char* function);

int ListIncrease(List* list);

int ListDecrease(List* list);

bool ListSort(List* list);

bool ListInit(List* list, int size = INITSIZE);

int ValueSearch(List* list, Elem_t value);

int UsageSize(List* list);

int NumberSearch(List* list, int number);

int PushPrev(List* list, Elem_t value, int number);

int PushNext(List* list, Elem_t value, int number);

int PushLast(List* list, Elem_t value);

int PushFirst(List* list, Elem_t value);

int PopFirst(List* list);

int ListFill(List* list, Elem_t min = 0, int amount = 1, Elem_t step = 0);

int ListDeletePH(List* list, int number);

bool ListKill(List* list);
