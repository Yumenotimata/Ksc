#include "mycc.h"
 
int main()
{
   char code[] = "(3+3)*3>2*(23*(3+4))";
    Token *head =  doTokenize(code);
    //misutta
    head = head->next;
    Node *node = expr(&head);
    printf("\n\ngenerateCode\n");
    generateCode(node);
    
    return 0;
}

