#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int fork_hello() {
    pid_t pid;

    // fork a child
    pid = fork();

    if (pid < 0) // error occured file fork
    {
        fprintf(stderr, "fork failed");
        return 1;
    }
    else if (pid == 0) // child process
    {
        // execlp("/bin/ls","ls",NULL);
        printf("hello world from child!\n");
    }
    else
    {
        wait(NULL);
        printf("Child Complete. child PID: %d\n",pid);
    }

    return 0;
}