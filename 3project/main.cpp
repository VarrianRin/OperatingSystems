#include "3project_lib.h"

int main(int argc, const char* argv[]) {

    if (argc != 4) {
        printf("ERROR, 4 arguments needed0");
    }

    const char* InputFile  = argv[1];
    const char* OutputFile = argv[2];
    int         period     = atoi(argv[3]);

    FILE* Output = fopen(OutputFile, "w");

    int Nprocs   = 0;
    int AllTime  = 0;

    proc       *procs = TextParser(InputFile, &Nprocs, &AllTime);
    time_elem* income = ProcIncome(procs, Nprocs, AllTime);

    //setbuf(stdout, 0);
    //WriteProcs(procs, Nprocs);
    //WriteIncome(income, AllTime);

    algorithm als[Nal];
    AlsInit(als, procs, Nprocs, Output);

    for (int ac = 0; ac < Nal; ac++) {

        fprintf(Output, "***** %s Scheduling *****\n", als[ac].name);
        for(int tc = 0, pc = 0; OneClock(income[tc], &(als[ac]), tc, period, &pc, Nprocs, Output) < Nprocs; tc++) {
           // ListDump(als[ac].schedule, __FILE__, __LINE__, __PRETTY_FUNCTION__);
           // WriteProcs(als[ac].procs, Nprocs);
           // printf("%d pc = %d\n\n", tc, pc);
        }
        AlgFinish(&als[ac], Nprocs, Output);
    }

    OverallSummary(als, Output);

    free(procs);
    for(int ac = 0; ac < Nal; ac++) {
        ListKill(als[ac].schedule);
        ListKill(als[ac].sequence);
        free(als[ac].procs);
    }
    for(int tc = 0; tc < AllTime; tc++) {
        if (income[tc].n_proc)
            free(income[tc].ArrivalProc);
    }
    fclose(Output);
    free(income);

    //assert(procs == NULL);
    return 0;
}
