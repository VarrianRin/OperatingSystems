#include "3project_lib.h"

int WriteProcs(struct proc* procs, int Nprocs) {

    int i = 0;
    for( ;  i < Nprocs; i++) {
        printf("P%d: %d %d %d, status %d, TA %d, WA %d\n", procs[i].index, procs[i].burst,
                                                        procs[i].priority, procs[i].arrival,
                                                        procs[i].status, procs[i].TT_time, procs[i].WT_time);
    }
    return i;
}

int WriteIncome(struct time_elem* income, int AllTime) {

    int i = 0;
    for( ;  i < AllTime; i++) {

        if (income[i].n_proc) {
            printf("At %d time %d processes arrives:", i, income[i].n_proc);
            for (int j = 0; j < income[i].n_proc; j++)
                printf(" %d", income[i].ArrivalProc[j]);

            printf("\n");
        }
    }
    return i;
}

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

int ProcParser (char* text, int SizeFile, struct proc* procs, int* AllTime) {

    assert(text != NULL);
    assert(procs != NULL);

    int line = 0;
    procs[line].index = line;
    sscanf(text, "%d %d %d", &procs[line].burst, &procs[line].priority, &procs[line].arrival);
    *AllTime += procs[line].burst;
    line++;

    for ( ; (text = strchr(text + 1, '\n')) != NULL; line++) {

        procs[line].index   = line;
        sscanf(text, "%d %d %d", &procs[line].burst, &procs[line].priority, &procs[line].arrival);
        *AllTime += procs[line].burst;

        procs[line].status  = ABSENT;
        procs[line].TT_time = 0;
        procs[line].WT_time = 0;
    }
    return line;
}

struct proc* TextParser(const char* FileName, int* Nprocs, int* AllTime) {

    int SizeFile = 0;
    char* text = WinReader(FileName, &SizeFile);
    assert (text != NULL);

    *Nprocs = LineCounter(text);
    proc* procs = (proc*) calloc(*Nprocs, sizeof(proc));

    int ParsReturn = ProcParser(text, SizeFile, procs, AllTime);
    assert(ParsReturn == *Nprocs);
    free(text);

    return procs;
}

time_elem* ProcIncome(struct proc* procs, int Nprocs, int AllTime) {

    time_elem* income      = (time_elem*) calloc(AllTime, sizeof(time_elem));
    int        tc          = 0;
    int        n_proc      = 0;

    for(int pc = 0; pc < Nprocs + 1; pc++) {

        if (pc == Nprocs || tc != procs[pc].arrival) {
            if (n_proc) {

                income[tc].n_proc      = n_proc;
                income[tc].ArrivalProc = (int*) calloc(n_proc, sizeof(int));

                for(int i = 0; i < n_proc; i++)
                    income[tc].ArrivalProc[i] = pc - n_proc + i;

                n_proc = 0;
            }
            if (pc == Nprocs)
                return income;

            for (; tc < AllTime; tc++)
                if (tc == procs[pc].arrival)
                    break;
        }

        if (tc == procs[pc].arrival) {
             n_proc++;
        }
    }
    return income;
}

int AssignProc(proc* procs, algorithm* als, int Nprocs) {

    als->procs = (proc*) calloc(Nprocs, sizeof(*procs));
    for(int i = 0; i < Nprocs; i++) {

        als->procs[i].initburst = procs[i].burst;
        als->procs[i].index     = procs[i].index;
        als->procs[i].arrival   = procs[i].arrival;
        als->procs[i].burst     = procs[i].burst;
        als->procs[i].priority  = procs[i].priority;
        als->procs[i].status    = procs[i].status;
        als->procs[i].WT_time   = procs[i].WT_time;
        als->procs[i].TT_time   = procs[i].TT_time;
        als->procs[i].RRblocks  = procs[i].RRblocks;
    }
    return 1;

}

int ComparePriority(const void* a, const void* b) {
    proc* proc1 = (proc*) a;
    proc* proc2 = (proc*) b;

    if (proc1->priority > proc2->priority)
        return 1;
    else if (proc1->priority < proc2->priority)
        return -1;
    else {
        if (proc1->index > proc2->index)
            return 1;
        else if (proc1->index < proc2->index)
            return -1;
    }
    return 0;
}

int CompareBurst(const void* a, const void* b) {
    proc* proc1 = (proc*) a;
    proc* proc2 = (proc*) b;

    if (proc1->burst > proc2->burst)
        return 1;
    else if (proc1->burst < proc2->burst)
        return -1;
    else {
        if (proc1->index > proc2->index)
            return 1;
        else if (proc1->index < proc2->index)
            return -1;
    }

    return 0;
}

int SortSchedule(algorithm* Al) {

    //ListDump(Al->schedule, __FILE__, __LINE__, __PRETTY_FUNCTION__);
    int size = UsageSize(Al->schedule);
    proc* ScheduleElements = (proc*) calloc(size, sizeof(proc));

    for(int i = Al->schedule->head, j = 0, n_pr = -1; i != 0; i = Al->schedule->Elem[i].next, j++) {

        n_pr = Al->schedule->Elem[i].data;
        ScheduleElements[j].index = n_pr;

        if      (Al->index == SJF || Al->index == STCF) ScheduleElements[j].burst    = Al->procs[n_pr].burst;
        else if (Al->index == Priority)                 ScheduleElements[j].priority = Al->procs[n_pr].priority;
    }

    if (Al->index == SJF || Al->index == STCF)
        qsort(ScheduleElements, size, sizeof(proc), CompareBurst);
    else if (Al->index == Priority)
        qsort(ScheduleElements, size, sizeof(proc), ComparePriority);

    //WriteProcs(ScheduleElements, size);
    for(int i = Al->schedule->head, j = 0; i != 0; i = Al->schedule->Elem[i].next, j++)
        Al->schedule->Elem[i].data = ScheduleElements[j].index;

    //ListDump(Al->schedule, __FILE__, __LINE__, __PRETTY_FUNCTION__);
    return 1;
}

int ProcCheck(proc* procs, algorithm* Al, int Nprocs) {

    int pc = 0;
    for( ; pc < Nprocs; pc++) {
        //if (procs[pc].index == 2) WriteProcs(&(procs[pc]), 1);

        if (procs[pc].status == QUEUE || procs[pc].status == WAITING) {
            procs[pc].WT_time++;
            procs[pc].TT_time++;
            procs[pc].RRblocks = 0;

            if(AGING != 0 && !(procs[pc].WT_time % AGING)) { //// AGING EXTRA CREDIT
                procs[pc].priority--;
                SortSchedule(Al);
            }
        }
        else if (procs[pc].status == RUNNING) {
            procs[pc].TT_time++;
            procs[pc].RRblocks++;
        }
        else if (procs[pc].status == PREEMPTED) {
            procs[pc].WT_time++;
            procs[pc].TT_time++;
            procs[pc].RRblocks = 0;

            if(AGING != 0 && !(procs[pc].WT_time % AGING)) { //// AGING EXTRA CREDIT
                procs[pc].priority--;
                SortSchedule(Al);
            }
            procs[pc].status = QUEUE;
        }
        else if (procs[pc].status == LOADING) {
            procs[pc].TT_time++;
            procs[pc].status = RUNNING;
            procs[pc].RRblocks++;
        }
        else if (procs[pc].status == FINISHING) {
            procs[pc].RRblocks = 0;
            procs[pc].status = FINISHED;
        }
        else if (procs[pc].status == IO) {

        }
    }
    return pc;
}

char* WriteQueue(List* schedule) {

    char* max_phrase = (char*) calloc(MAXQUEUE, sizeof(char));

    if(schedule->head == 0)
        sprintf(max_phrase, "empty\n");

    else {
        int count = 0;
        for(int i = schedule->head; i != schedule->tail; i = schedule->Elem[i].next) {
            sprintf(max_phrase + count, "%d-", schedule->Elem[i].data);
            count += 2;
        }

        sprintf(max_phrase + count, "%d\n", schedule->Elem[schedule->tail].data);
    }

    int length = strlen(max_phrase);
    char* phrase = (char*) calloc(length + 1, sizeof(char));
    for(int i = 0; i < length; i++) phrase[i] = max_phrase[i];

    free(max_phrase);

    return phrase;
}

int WriteLoading(write_pattern* pattern, FILE* Output) {
    return fprintf(Output, "Loading process %d (CPU burst = %d)\nReady queue: %s\n", pattern->first, pattern->second, pattern->queue);
}

int WriteRunning(write_pattern* pattern, FILE* Output) {
    return fprintf(Output, "Running process %d (remaining CPU burst = %d)\nReady queue: %s\n", pattern->first, pattern->second, pattern->queue);
}

int WriteFinishingLoading(write_pattern* pattern, FILE* Output) {
    return fprintf(Output, "Finishing process %d; loading process %d (CPU burst = %d)\nReady queue: %s\n", pattern->first, pattern->second, pattern->third, pattern->queue);
}

int WriteFinishing(write_pattern* pattern, FILE* Output) {
    return fprintf(Output, "Finishing process %d\nReady queue: %s\n", pattern->first, pattern->queue);
}
int WritePreempted(write_pattern* pattern, FILE* Output) {
    return fprintf(Output, "Preempting process %d (remaining CPU burst = %d); loading process %d (CPU burst = %d)\nReady queue: %s\n", pattern->first, pattern->second, pattern->third, pattern->forth, pattern->queue);
}

output_phrase ProcessesSituation(algorithm* Al, int* pc, int Nprocs, int* place, int tc, FILE* Output) {

    write_pattern* pattern = (write_pattern*) calloc(1, sizeof(write_pattern));
    int next_el = Al->schedule->head;
    if (Output != nullptr) pattern->queue = WriteQueue(Al->schedule);

    ////---------- LOADING SITUATION ----------
    if(Al->running == -1 && next_el != 0) {

        pattern->phrase = Loading;
        if (Output != nullptr) {
            int next_pr = Al->schedule->Elem[next_el].data;
            pattern->first = next_pr;
            pattern->second = Al->procs[next_pr].burst;
            WriteLoading(pattern, Output);
        }
    } ////---------- FINISHING SITUATION ----------
    else if(Al->running != -1 && next_el == 0 && Al->procs[Al->running].burst == 1) {

        pattern->phrase = Finishing;
        if (Output != nullptr) {
            pattern->first = Al->running;
            WriteFinishing(pattern, Output);
        }
    } ////---------- FINISHING AND LOADING SITUATION ----------
    else if(Al->running != -1 && next_el != 0 && Al->procs[Al->running].burst == 1) {

        pattern->phrase = FinishingLoading;
        if (Output != nullptr) {
            int next_pr = Al->schedule->Elem[next_el].data;
            pattern->first = Al->running;
            pattern->second = next_pr;
            pattern->third = Al->procs[next_pr].burst;
            WriteFinishingLoading(pattern, Output);
        }
    } ////---------- PREEMPTING SITUATION ----------
    else if (next_el != 0 && ((Al->index == STCF && Al->procs[Al->schedule->Elem[next_el].data].burst < Al->procs[Al->running].burst - 1) || (Al->index == RoundRobin && (Al->procs[Al->running].RRblocks >= Al->RRquant)))) {

        pattern->phrase = Preempted;
        if (Output != nullptr) {
            int next_pr = Al->schedule->Elem[next_el].data;
            pattern->first  = Al->running;
            pattern->second = Al->procs[Al->running].burst - 1;
            pattern->third  = next_pr;
            pattern->forth  = Al->procs[next_pr].burst;
            WritePreempted(pattern, Output);
        }

    } ////---------- RUNNING SITUATION ----------
    else if(Al->running != -1 && Al->procs[Al->running].burst > 1) {

        pattern->phrase = Running;
        if (Output != nullptr) {
            pattern->first = Al->running;
            pattern->second = Al->procs[Al->running].burst - 1;
            WriteRunning(pattern, Output);
        }
    }
    else {
        //fprintf(Output, "\n\nEEEEEEEERRRRRRRROOOOOOORRRRRRR\nUnexpected Behaviour\n\n");
    }

    output_phrase phrase = pattern->phrase;
    free(pattern->queue);
    free(pattern);
    return phrase;
}

output_phrase Process(algorithm* Al, int* pc, int Nprocs, int tc, FILE* Output) {

    int place = 0;
    output_phrase situation = ProcessesSituation(Al, pc, Nprocs, &place, tc, Output);

    if (situation == Finishing || situation == Loading || situation == FinishingLoading) {

        if (situation == Finishing || situation == FinishingLoading) {

            Al->procs[Al->running].burst--;
            Al->procs[Al->running].status = FINISHING;
            (*pc)++;
        }

        if (situation == FinishingLoading || situation == Loading) {

            Al->running = PopFirst(Al->schedule);
            Al->procs[Al->running].status = LOADING;
            PushLast(Al->sequence, Al->running);
            (Al->Nswitches)++;

            return situation;
        }
        else if (situation == Finishing)
            return situation;
    }
    else if (situation == Running) {

        Al->procs[Al->running].burst--;
        return situation;
    }
    else if (situation == Preempted) {

        Al->procs[Al->running].burst--;
        Al->procs[Al->running].status = PREEMPTED;

        if (Al->index == RoundRobin) {
            PushLast(Al->schedule, Al->running);
        }
        else if (Al->index == STCF) {

            bool not_last = false;

            for(int i = Al->schedule->head; i != 0; i = Al->schedule->Elem[i].next) {
                if (Al->procs[Al->schedule->Elem[i].data].burst >= Al->procs[Al->running].burst) {
                    //ListDump(Al->schedule, __FILE__, __LINE__, __PRETTY_FUNCTION__);
                    PushPrev(Al->schedule, Al->running, i);
                    not_last = true;
                    break;
                }
            }
            if (!not_last) {
                PushLast(Al->schedule, Al->running);
            }

        }
        else {
            //fprintf(Output, "\n\nEEEEEEEERRRRRRRROOOOOOORRRRRRR\nUnexpected Behaviour\n\n");
        }

        Al->running = PopFirst(Al->schedule);
        Al->procs[Al->running].status = LOADING;
        PushLast(Al->sequence, Al->running);
        (Al->Nswitches)++;
        return situation;
    }

    return situation;
}




int OneClock(time_elem income, algorithm* Al, int tc, int period, int* pc, int Nprocs, FILE* Output) {

    if (income.n_proc > 0) {
        for (int i = 0; i < income.n_proc; i++) {

            PushLast(Al->schedule, income.ArrivalProc[i]);
            Al->procs[income.ArrivalProc[i]].status = QUEUE;
        }
        if (Al->index == SJF || Al->index == STCF || Al->index == Priority)
            SortSchedule(Al);
    }

    //if (income.n_proc) ListDump(Al->schedule, __FILE__, __LINE__, __PRETTY_FUNCTION__);

    bool print = !(tc % period);
    if (print)
        fprintf(Output, "t = %d\nCPU: ", tc);

    if (print) Process(Al, pc, Nprocs, tc, Output);
    else       Process(Al, pc, Nprocs, tc);

    ProcCheck(Al->procs, Al, Nprocs);

    return *pc;
}

int AlgFinish(algorithm* als, int Nprocs, FILE* Output) {

    fprintf(Output, "*********************************************************\n");
    fprintf(Output, "%s Summary (WT = wait time, TT = turnarond time):\n\nPID\t\tWT\t\tTT\n", als->name);

    for(int pc = 0; pc < Nprocs; pc++) {
        als->TT_time += als->procs[pc].TT_time;
        als->WT_time += als->procs[pc].WT_time;
        fprintf(Output, "%d\t\t%d\t\t%d\n", pc, als->procs[pc].WT_time, als->procs[pc].TT_time);
    }
    als->WT_time = als->WT_time / Nprocs;
    als->TT_time = als->TT_time / Nprocs;
    fprintf(Output, "AVG\t\t%.2f\t\t%.2f\n\n", als->WT_time, als->TT_time);

    fprintf(Output, "Process sequence: ");
    for(int i = als->sequence->head; i != als->sequence->tail; i = als->sequence->Elem[i].next)
        fprintf(Output, "%d-", als->sequence->Elem[i].data);
    fprintf(Output, "%d\n", als->sequence->Elem[als->sequence->tail].data);

    fprintf(Output, "Context switches: %d\n\n", als->Nswitches);

    als->running = -1;

    return 0;
}


void AlsInit(algorithm* als, proc* procs, int Nprocs, FILE* Output) {

    //if (Nal != 5)
    //    fprintf(Output, "ERROR HAPPENED WHEN INITIALIZING");

    als[0].name = "FCFS";
    als[1].name = "SJF";
    als[2].name = "STCF";
    als[3].name = "Round robin";
    als[4].name = "Priority";
    alg_indexes index[5] = {FCFS, SJF, STCF, RoundRobin, Priority};

    for(int ac = 0; ac < Nal; ac++) {

        als[ac].WT_time   = 0;
        als[ac].TT_time   = 0;
        als[ac].Nswitches = 0;
        als[ac].index     = index[ac];
        als[ac].running   = -1;
        als[ac].RRquant   = 2;
        AssignProc(procs, &(als[ac]), Nprocs);

        List* schedule = (List*) calloc(1, sizeof(List));
        ListInit(schedule, Nprocs);
        als[ac].schedule = schedule;

        List* sequence = (List*) calloc(1, sizeof(List));
        ListInit(sequence, Nprocs);
        als[ac].sequence = sequence;

        List* IOqueue = (List*) calloc(1, sizeof(List));
        ListInit(IOqueue, Nprocs);
        als[ac].IOqueue = IOqueue;
    }
}

int CompareWT(const void* a, const void* b)
{
    algorithm* al1 = (algorithm*) a;
    algorithm* al2 = (algorithm*) b;

    if (al1->WT_time > al2->WT_time)
        return 1;
    else if (al1->WT_time < al2->WT_time)
        return -1;

    return 0;
}

int CompareTT(const void* a, const void* b)
{
    algorithm* al1 = (algorithm*) a;
    algorithm* al2 = (algorithm*) b;
    if (al1->TT_time > al2->TT_time)
        return 1;
    else if (al1->TT_time < al2->TT_time)
        return -1;

    return 0;
}

int CompareNswitches(const void* a, const void* b)
{
    algorithm* al1 = (algorithm*) a;
    algorithm* al2 = (algorithm*) b;

    if (al1->Nswitches > al2->Nswitches)
        return 1;
    else if (al1->Nswitches < al2->Nswitches)
        return -1;

    return 0;
}

void OverallSummary(algorithm* als, FILE* Output) {

    fprintf(Output, "\n***** OVERALL SUMMARY *****\n");

    fprintf(Output, "\nWait Time Comparison\n");
    qsort(als, Nal, sizeof(algorithm), CompareWT);
    for(int ac = 0; ac < Nal; ac++) fprintf(Output, "%d %s %15.2f\n", ac+1, als[ac].name, als[ac].WT_time);

    fprintf(Output, "\nTurnaround Time Comparison\n");
    qsort(als, Nal, sizeof(algorithm), CompareTT);
    for(int ac = 0; ac < Nal; ac++) fprintf(Output, "%d %s %15.2f\n", ac+1, als[ac].name, als[ac].TT_time);

    fprintf(Output, "\nContext Switch Comparison\n");
    qsort(als, Nal, sizeof(algorithm), CompareNswitches);
    for(int ac = 0; ac < Nal; ac++) fprintf(Output, "%d %s %15d\n", ac+1, als[ac].name, als[ac].Nswitches);
}
