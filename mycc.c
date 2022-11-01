#include "mycc.h"
 
int main()
{
   char code[] = "2+3*4";
    Token *head =  doTokenize(code);
    //misutta
    head = head->next;
    
    Node *parse = expr(&head);
    parse = parse->rhs;
    parse = parse->rhs;
    printf("\n%d\n",parse->val);
    return 0;
}

