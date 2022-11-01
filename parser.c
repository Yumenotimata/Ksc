#include "mycc.h"

Node *parser(Token *opToken)
{
    Node *OpToken = opToken;
    expr(OpToken);
}

Node *expr(Token *opToken)
{
    printf("expr mul(opToken)\n");
    Node *retNode = mul(opToken);
    printf("expr returned from mul\n");
    opToken = opToken->next;
    printf("...%c..\n",opToken->str[0]);
    for(;;)
    {
        if(ifKigou(opToken,"+"))
        {
            opToken = opToken->next;
            retNode = makeNewNode(ND_ADD,retNode,mul(opToken));
        }
        else if(ifKigou(opToken,"-"))
        {
            opToken = opToken->next;
            retNode = makeNewNode(ND_SUB,retNode,mul(opToken));
        }else
        {
            printf("expr returned retNode\n");
            return retNode;
        }
    }
}

Node *mul(Token *opToken)
{
    printf("mull primary(opToken)\n");
    Node *retNode = primary(opToken);
    printf("mull returne from primary()\n");
    for(;;)
    {
        if(ifKigou(opToken,"*"))
        {
            opToken = opToken->next;
            Node *retNode = makeNewNode(ND_MUL,retNode,primary(opToken));
            printf("*\n");
        }else if(ifKigou(opToken,"/"))
        {
            opToken = opToken->next;
            Node *retNode = makeNewNode(ND_DIV,retNode,primary(opToken));
            printf("/\n");
        }
        else
        {
            printf("mul returned retNode\n");
            return retNode;
        }
    }
}

Node *primary(Token *opToken)
{
    if(ifKigou(opToken,"("))
    {
        Node *retNode = expr(opToken);
        opToken = opToken->next;
        if(opToken->str[0] != ')')
        {
            printf("')' is not exit");
            exit(1);
        } 
        return retNode;
    }
    Node *retNode = makeNewNumNode(opToken->val);
    opToken = opToken->next;
    //printf("%c\n",opToken->str[0]);
    printf("primary retuened retNode\n");
    return retNode;
}

bool ifKigou(Token *opToken,char *str)
{
    if(opToken->kind != TK_KIGOU || memcmp(opToken->str,str,strlen(str)))
    {
        return false;
    }
    return true;
}

Node *makeNewNode(NodeKind kind,Node *lhs,Node*rhs)
{
    Node *retNode = calloc(1,sizeof(Node));
    retNode->rhs = rhs;
    retNode->lhs = lhs;
    retNode->kind = kind;
}

Node *makeNewNumNode(int val)
{
    Node *retNode = calloc(1,sizeof(Node));
    retNode->val = val;
    retNode->kind = ND_NUM;
    return retNode;
}