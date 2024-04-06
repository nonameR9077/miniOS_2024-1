#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "system.h"
#include "fork.h"
void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;

    while(1) {
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");
        
	if (strcmp(input,"exit") == 0) {
            break;
        }

    else if (strcmp(input,"minisystem") == 0){
        minisystem();
    }

	else if (strcmp(input,"add") == 0){
        printf("%d\n", add());
	}

    else if (strcmp(input,"fork") == 0){
	    fork_hello();
	}
    
    else system(input);
    }

    // 메모리 해제
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
