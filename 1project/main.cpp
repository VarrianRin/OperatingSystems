#include <sys/types.h>		// Needed for pid_t data type
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>			// Needed for system calls
#include <cstdlib>


int main(int argc, char *argv[]) {

	char filenames[][14] = {"./test1/test1",
						  	"./test2/test2",
						  	"./test3/test3",
						  	"./test4/test4",
						  	"./test5/test5",};
						  
    int NumChild = (argc == 2) ? atoi(argv[1]) : 1;
    pid_t* pid = (pid_t*) calloc(NumChild, sizeof(pid_t));
    int count = 0;

    for (int i = 0; i < NumChild; i++) {

        pid[i] = fork();
        if (pid[i] != 0) {
            printf("Started child %d with pid %d\n", i + 1, pid[i]);
        }
        else {
            count += i + 1;
            break;
        }
    }
    
    if (count != 0) {
	
		//printf("%d: %d, %d\n", count, pid[0], pid[1]);
	
  		//printf("%d: %s\n", count, filenames[count % 5 - 1]);
	    execlp(filenames[(count - 1) % 5], NULL);
	}
	
    else if (count == 0) {

        pid_t pid_finished = 0;
        int   index        = 0;

        for (int i = 0; i < NumChild; i++) {
            pid_finished = wait(NULL);

            for (index = 0; index < NumChild; index++)
                if (pid[index] == pid_finished)
                    break;

            printf("Child %d (PID %d) finished\n", index + 1, pid_finished);
        }
    }
}
