#include "4project_lib.h"

extern int              Nprocs;
extern int              Nframes;
extern int              SizeRAM;
extern int              SizeFrame;
extern int*             RAM;
extern FILE*            OUTPUT;

extern sem_t            OutSem;
extern sem_t            MemSem;

extern procType*        proc;
extern PagePlaceType    PagePlace;


//! LineCounter\n
//! counts lines\n
//! @param [in]  text - text with lines
//! @param [out] NLines - number of lines in text

int LineCounter(const char* text) {

    assert(text != NULL);

    int NLines = 1;

    for ( ; (text = strchr(text + 1, '\n')) != NULL; NLines++)
        ;

    return NLines;
}

//! WinReader\n
//! only for Windows files\n
//! makes first and last symbol '\0'\n
//! @param [in]  FileName - pointer to file
//! @param [in]  SizeFile - size of file
//! @param [out] text (calloc) - pointer to text read
//! @warning initializing text (calloc)

char* WinReader (const char* FileName, int* SizeFile) {

    assert(FileName != NULL);

    FILE* TextFile = fopen(FileName, "rb");
    assert(TextFile != NULL);

    fseek(TextFile, 0L, SEEK_END);
    *SizeFile = ftell(TextFile);
    fseek(TextFile, 0L, SEEK_SET);

    char* text  = (char*) calloc(*SizeFile + 1, sizeof(text[0]));

    assert(text != NULL);

    int ReadReturn= fread(text, sizeof(text[0]), *SizeFile, TextFile);
    assert (ReadReturn == *SizeFile);
    fclose(TextFile);

    text[*SizeFile] = '\0';

    return text;
}

//! ProcParser\n
//! Only for Windows files\n
//! @param [in]  text - pointer to text
//! @param [in]  SizeFile - size of the file
//! @param [un]  Lines - strucu with pointers to lines and their sizes
//! @param [out] line - number of lines sorted

int ProcParser (char* text, int idx, int Nlines) {

    assert(text != NULL);
    int  line  = 0;
    char mode  = -1;
    char blank = 0;
    int  reg   = -1;
    int  adr   = -1;
    int  value = -1;

    sscanf(text, "%d", &proc[idx].VirtualSize);
    proc[idx].TableSize = proc[idx].VirtualSize / SizeFrame;
    line++;
    proc[idx].max_access        = Nlines - 1;
    proc[idx].access            = (long int*) calloc (proc[idx].max_access, sizeof(long int));
    proc[idx].current_access    = 0;

    for (int i = 0; (text = strchr(text + 1, '\n')) != nullptr; line++, i++) {

        //printf("!%s!\n", text + 1);
        sscanf(text + 1, "%c%c%c%d %d", &mode, &blank, &blank, &reg, &adr);
        //printf("'%c, %d, %d'\n", mode, reg, adr);
        value = adr * 1000;
        value += reg * 10;
        if (mode == 'R')
            value += 0;
        else if (mode == 'W')
            value += 1;

        proc[idx].access[i] = value;
        //printf("'%d: %d'\n", idx, value);
    }
    return line;
}

//! InputParser\n
//! Only for Windows files\n
//! @param [in]  text - pointer to text
//! @param [in]  SizeFile - size of the file
//! @param [un]  Lines - strucu with pointers to lines and their sizes
//! @param [out] line - number of lines sorted

int InputParser (char* text) {

    assert(text != NULL);
    int line = 0;

    sscanf(text, "%d", &SizeRAM);
    line++;
    text = strchr(text + 1, '\n');

    sscanf(text, "%d", &SizeFrame);
    line++;
    Nframes = SizeRAM / SizeFrame;
    text = strchr(text + 1, '\n');

    sscanf(text, "%d", &Nprocs);
    line++;

    proc = (procType*) calloc (Nprocs, sizeof(procType));

    for (int i = 0; (text = strchr(text + 1, '\n')) != nullptr; line++, i++) {

        sscanf(text, "%s", proc[i].FileName);
        proc[i].index = i;

    }
    return line;
}

int TextParser(const char* FileName, bool PROC_PARS, int idx) {

    int SizeFile    = 0;
    char* text      = WinReader(FileName, &SizeFile);
    assert (text != NULL);

    int ParsReturn = 0;
    int Nlines      = LineCounter(text);
    if(!PROC_PARS)
        ParsReturn  = InputParser(text);
    else
        ParsReturn  = ProcParser(text, idx, Nlines);

    assert(ParsReturn == Nlines);
    free(text);

    return Nlines;
}

int* InitRAM(int seed){

    int* RAM = (int*) calloc(SizeRAM,sizeof(int));
    srand(seed);

    for (int i = 0; i < SizeRAM; i++)
        RAM[i] = rand();

    return RAM;
}

int InitProcs() {

    ListInit(&PagePlace.Clock, Nframes + 1);
    int res = ListFill(&PagePlace.Clock, 0, Nframes, 1);
    assert(res == Nframes - 1);

    PagePlace.Clock.Elem[PagePlace.Clock.tail].next = PagePlace.Clock.head;
    PagePlace.Clock.Elem[PagePlace.Clock.head].prev = PagePlace.Clock.tail;

    PagePlace.frame = (FrameType*) calloc(Nframes, sizeof(FrameType));
    for(int i = 0; i < Nframes; i++, PagePlace.frame[i].FrameOwner = nullptr) {
        PagePlace.frame[i].min_adress = i * SizeFrame;
        PagePlace.frame[i].max_adress = (i + 1) * SizeFrame - 1;
    }
    PagePlace.CurrentPlace = &(PagePlace.Clock.Elem[PagePlace.Clock.head]);

    int i = 0;
    for ( ; i < Nprocs; i++) {
        TextParser(proc[i].FileName, 1, i);
        proc[i].PageTable = (transl*) calloc(proc[i].TableSize, sizeof(transl));
        for(int j = 0; j < proc[i].TableSize; j++) {
            proc[i].PageTable[j].procs      = i;
            proc[i].PageTable[j].idx_page   = j;
            proc[i].PageTable[j].min_adress = j * SizeFrame;
            proc[i].PageTable[j].max_adress = (j + 1) * SizeFrame - 1;

        }
    }
    return i;
}

int Translate(int id, int VA, int page, int frame, bool old) {

    int PA    = PagePlace.frame[frame].min_adress + VA - proc[id].PageTable[page].min_adress;
    PagePlace.frame[frame].ref = true;

    sem_wait(&OutSem);
    if (old)
        fprintf(OUTPUT, "P%d: valid translation from page %d to frame %d\n", id, page, frame);
    else
        fprintf(OUTPUT, "P%d: new translation from page %d to frame %d\n", id, page, frame);

    fprintf(OUTPUT, "P%d: translated VA 0x%08x to PA 0x%08x\n", id, VA, PA);
    sem_post(&OutSem);

    return  PA;
}

int FindPlace(int id, int VA, transl* translation) {

    sem_wait(&OutSem);
    fprintf(OUTPUT, "P%d: page %d not resident in memory\n", id, translation->idx_page);
    sem_post(&OutSem);

    while(true) {
        int CurrentFrame = PagePlace.CurrentPlace->data;
        if (PagePlace.frame[CurrentFrame].FrameOwner == nullptr) {

            sem_wait(&OutSem);
            fprintf(OUTPUT, "P%d: using free frame %d\n", id, CurrentFrame);
            sem_post(&OutSem);

            PagePlace.frame[CurrentFrame].ref        = true;
            PagePlace.frame[CurrentFrame].FrameOwner = translation;
            translation->idx_frame                   = CurrentFrame;
            translation->valid                       = true;

            break;
        }
        else if (PagePlace.frame[CurrentFrame].ref) {
            PagePlace.frame[CurrentFrame].ref = false;
            PagePlace.CurrentPlace = &(PagePlace.Clock.Elem[PagePlace.CurrentPlace->next]);
            continue;
        }
        else if (!PagePlace.frame[CurrentFrame].ref) {
            //printf("EVICT %d: %d, page%d, valid%d, from %d to %d, frame%d'\n", id, VA, translation->idx_page, translation->valid, translation->min_adress, translation->max_adress, translation->idx_frame);
            sem_wait(&OutSem);
            fprintf(OUTPUT, "P%d: evicting process %d, page %d from frame %d\n", id, PagePlace.frame[CurrentFrame].FrameOwner->procs, PagePlace.frame[CurrentFrame].FrameOwner->idx_page, PagePlace.frame[CurrentFrame].FrameOwner->idx_frame);
            sem_post(&OutSem);

            (PagePlace.frame[CurrentFrame].FrameOwner)->valid   = false;
            PagePlace.frame[CurrentFrame].ref                   = true;
            PagePlace.frame[CurrentFrame].FrameOwner            = translation;
            translation->idx_frame                              = CurrentFrame;
            translation->valid                                  = true;
            break;
        }
    }
    PagePlace.CurrentPlace = &(PagePlace.Clock.Elem[PagePlace.CurrentPlace->next]);
    //printf("'%d: %d, page%d, valid%d, from %d to %d, frame%d'\n", id, VA, translation->idx_page, translation->valid, translation->min_adress, translation->max_adress, translation->idx_frame);
}

int MemAccess(int id, int adress, int value) {

    sem_wait(&MemSem);

    //printf("!%d: %d, %d'\n", id, adress, value);
    /*
    sem_wait(&OutSem);
    int count = 0;
    int procc = -1;
    for(Element* node = PagePlace.CurrentPlace; count < Nframes; node = &PagePlace.Clock.Elem[node->next], count++) {

        if (PagePlace.frame[node->data].FrameOwner)
            procc = PagePlace.frame[node->data].FrameOwner->procs;
        else
            procc = -1;

        printf("PRINT CLOCK: frame%d, proc%d ref%d from %d to %d\n", node->data, procc, PagePlace.frame[node->data].ref, PagePlace.frame[node->data].min_adress, PagePlace.frame[node->data].max_adress);
    }
    sem_post(&OutSem);*/

    int PA = -1;
    for (int i = 0; i < proc[id].TableSize + 1; i++) {
        //printf("%d search %d: %d %d %d valid%d\n", id, i,proc[id].PageTable[i].min_adress, adress, proc[id].PageTable[i].max_adress, proc[id].PageTable[i].valid);
        if ((proc[id].PageTable[i].min_adress <= adress && proc[id].PageTable[i].max_adress >= adress) && proc[id].PageTable[i].valid) {
            PA = Translate(id, adress, proc[id].PageTable[i].idx_page, proc[id].PageTable[i].idx_frame);
            break;
        }
        if ((proc[id].PageTable[i].min_adress <= adress && proc[id].PageTable[i].max_adress >= adress) && !proc[id].PageTable[i].valid) {
            FindPlace(id, adress, &proc[id].PageTable[i]);
            PA = Translate(id, adress, proc[id].PageTable[i].idx_page, proc[id].PageTable[i].idx_frame, false);
            break;
        }
    }
    if (value == POISON)
        value = RAM[PA];
    else
        RAM[PA] = value;
    sem_post(&MemSem);

    return value;
}

void* ExecuteProc(void *arg) {

    tinfo_t *t  = (tinfo_t *) arg;
    int id  = t->thread_id;
    //printf("proc : %d\n", id);

    sem_wait(&OutSem);
    fprintf(OUTPUT, "Process %d started\n", id);
    sem_post(&OutSem);

    for(int i = 0; i < proc[id].max_access; i++) {

        char mode  = (proc[id].access[i] % 10 == 0) ? 'R' : 'W';
        int  reg   = (proc[id].access[i] % 1000) /10;
        int  adr   = proc[id].access[i] / 1000;
        int  value = 0;

        sem_wait(&OutSem);
        fprintf(OUTPUT, "P%d OPERATION: %c r%d %d\n", id, mode, reg, adr);
        sem_post(&OutSem);

        if (mode == 'R') {
            value = MemAccess(id, adr);
            proc[id].Registers[reg] = value;
        }
        else if (mode == 'W') {
            value = MemAccess(id, adr, proc[id].Registers[reg]);
        }

        sem_wait(&OutSem);
        fprintf(OUTPUT, "P%d: r%d = 0x%08x (mem at virtual addr 0x%08x) \n", id, reg, value, adr);
        sem_post(&OutSem);
    }

    sem_wait(&OutSem);
    fprintf(OUTPUT, "Process %d completed\n", id);
    sem_post(&OutSem);
    void* result;
    pthread_exit(result);
    return result;
}
