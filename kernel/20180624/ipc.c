#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1 

int ipc()
{
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;
    
    if(pipe(fd) == -1) { //createthepipefprintf
        fprintf(stderr,"Pipe failed");
        return 1;
    }
    
    pid =fork();  //fork a child process 
    
    if (pid <0) {   /* error occurred*/
        fprintf(stderr,"Fork Failed");
        return 1;
    }
    
    if(pid > 0) {    /*parent process*/
        close(fd[READ_END]);    // close the unused end of the pipe
        /*write to the pipe*/
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        printf("write msg : %s\n", write_msg);
        /*close the write end of the pipe*/
        close(fd[WRITE_END]);

        wait(0);
    }
    else {  /*child process*/
        /*close the unused end of the pipe*/ 
        close(fd[WRITE_END]);
        /*read from the pipe*/
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("read msg : %s\n", read_msg);
        /*close the read end of the pipe*/
        close(fd[READ_END]);

        exit(0);
    }
    
    return 0;
}