#include <stdio.h>
#include <stdlib.h>

void minisystem()
{
    printf("minisystem\n");
}

int add()
{
    int a,b;
    
    printf("enter first integer...  ");
    scanf("%d", &a);

    printf("enter second integer...  ");
    scanf("%d", &b);

    return a+b;
}
