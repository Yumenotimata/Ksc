#include "mycc.h"
 
int main()
{
   char code[] = "((1+4)*5)/4+54*(34+2*2)";
    Token *head =  doTokenize(code);
    //misutta
    head = head->next;
    
    Node *node = expr(&head);
    printf("\n\ngenerateCode\n");
    generateCode(node);
    return 0;
}

