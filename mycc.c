#include "mycc.h"
 
int main()
{
   char code[] = "1+3";
    Token *head =  doTokenize(code);
    //misutta
    head = head->next;
    
    Node *parse = parser(head);
    
    return 0;
}

