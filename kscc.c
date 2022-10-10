#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    //char *p = argv[1];
    char *p = "1+5+6";

    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");

    printf("    mov rax,%ld\n",strtol(p,&p,10));
    
    while(*p)
    {
        if(*p == '+')
        {
            p++;
            printf("    add rax,%ld\n",strtol(p,&p,10));
            continue;
        }

        if(*p == '-')
        {
            p++;
            printf("    sub rax,%ld\n",strtol(p,&p,10));
            continue;
        }

        printf("failed to understand '%c'",*p);
        return 1;
    }

    printf("    ret\n");
    return 0;
}