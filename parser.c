#include "mycc.h"


Node *expr(Token **opToken)
{
    return equality(opToken);
    // printf("expr mul(opToken)\n");
    // Node *retNode = mul(opToken);
    // printf("expr returned from mul\n");

    // for(;;)
    // {
    //     if(ifKigou(opToken,"+"))
    //     {
    //         *opToken = (*opToken)->next;
    //         retNode = makeNewNode(ND_ADD,retNode,mul(opToken));
    //         printf("+\n");
    //     }
    //     else if(ifKigou(opToken,"-"))
    //     {
    //         *opToken = (*opToken)->next;
    //         retNode = makeNewNode(ND_SUB,retNode,mul(opToken));
    //         printf("-\n");
    //     }else
    //     {
    //         printf("expr returned retNode\n");
    //         return retNode;
    //     }
    // }
}

Node *equality(Token **opToken)
{
    Node *retNode = relational(opToken);
    printf("equality returned from mul\n");
    for(;;)
    {
        if(ifKigou(opToken,"=="))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_EQU,retNode,relational(opToken));
            return retNode;
        }
        if(ifKigou(opToken,"!="))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_NEQU,retNode,relational(opToken));
            return retNode;
        }
        else 
        {   
            return retNode;
        }
    }
}

Node *relational(Token **opToken)
{
    Node *retNode = add(opToken);

    for(;;)
    {
        if(ifKigou(opToken,"<"))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_SB,retNode,add(opToken));
        }
        if(ifKigou(opToken,"<="))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_ESB,retNode,add(opToken));
        }
        if(ifKigou(opToken,">"))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_BS,retNode,add(opToken));
        }
        if(ifKigou(opToken,">="))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_ESB,retNode,add(opToken));
        }

        return retNode;
    }
}

Node *add(Token **opToken)
{
    Node *retNode = mul(opToken);
    
    for(;;)
    {
        if(ifKigou(opToken,"+"))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_ADD,retNode,mul(opToken));
            printf("+\n");
        }
        else if(ifKigou(opToken,"-"))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_SUB,retNode,mul(opToken));
            printf("-\n");
        }
        else if(ifKigou(opToken,"<"))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_SB,retNode,mul(opToken));
        }
        else if(ifKigou(opToken,"<="))
        {
            *opToken = (*opToken)->next;
            printf("<=\n");
            retNode = makeNewNode(ND_ESB,retNode,mul(opToken));
        }
        else if(ifKigou(opToken,">"))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_SB,mul(opToken),retNode);
        }
        else if(ifKigou(opToken,"=>"))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_ESB,mul(opToken),retNode);
        }
        else
        {
            printf("expr returned retNode\n");
            return retNode;
        }
    }
    
}

Node *unary(Token **opToken)
{
    if(ifKigou(opToken,"+"))
    {
        *opToken = (*opToken)->next;
        return primary(opToken);
    }
    if(ifKigou(opToken,"-"))
    {
        *opToken = (*opToken)->next;
        Node *retNode = makeNewNode(ND_SUB,makeNewNumNode(0),primary(opToken));
        return retNode;
    }
    return primary(opToken);
}

Node *mul(Token **opToken)
{
    Node *retNode = unary(opToken);
    for(;;)
    {
        if(ifKigou(opToken,"*"))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_MUL,retNode,unary(opToken));
            printf("*\n");
        }else if(ifKigou(opToken,"/"))
        {
            *opToken = (*opToken)->next;
            retNode = makeNewNode(ND_DIV,retNode,unary(opToken));
            printf("/\n");
        }
        else
        {
            return retNode;
        }
    }
}

Node *primary(Token **opToken)
{

    if(ifKigou(opToken,"("))
    {
        *opToken = (*opToken)->next;
        Node *retNode = expr(opToken);
        
        if((*opToken)->str[0] != ')')
        {
            printf("')' is not exit");
            exit(1);
        } 
        *opToken = (*opToken)->next;
        return retNode;
    }
        printf("%d",(*opToken)->val);
    
    Node *retNode = makeNewNumNode((*opToken)->val);
    *opToken = (*opToken)->next;
    //printf("%c\n",opToken->str[0]);

    return retNode;
}

bool ifKigou(Token **opToken,char *str)
{
    if((*opToken)->kind != TK_KIGOU || memcmp((*opToken)->str,str,strlen(str)))
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