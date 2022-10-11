#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *str ="12+4";
    int i = strtol(str,&str,10);
    printf("%d",i+1);
    int d = strtol(str,&str,10); 
    printf("%d",d);
}
