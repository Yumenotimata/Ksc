#include "mycc.h"

void generateCode(Node *node)
{
    if(node->kind == ND_NUM)
    {
        printf("push %d\n",node->val);
        return;
    }

    generateCode(node->lhs);
    generateCode(node->rhs);

    switch(node->kind)
    {
        case ND_ADD:
            printf("pop rax\n");
            printf("pop rdi\n");
            printf("add rax,rdi\n");
            printf("push rax\n");
            break;
        case ND_SUB:
            printf("pop rax\n");
            printf("pop rdi\n");
            printf("add rax,rdi\n");
            printf("push rax\n");
            break;
        case ND_MUL:
            printf("pop rax\n");
            printf("pop rdi\n");
            printf("mul rax,rdi\n");
            printf("push rax\n");
            break;
        case ND_DIV:
            printf("pop rax\n");
            printf("pop rdi\n");
            printf("div rax,rdi\n");
            printf("push rax\n");
            break;
    }
}