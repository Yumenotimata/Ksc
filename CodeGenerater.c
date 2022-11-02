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
            printf("sub rax,rdi\n");
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
        case ND_EQU:
            printf("pop rax\n");
            printf("pop rdi\n");
            printf("cmp rax,rdi\n");
            printf("sete al\n");
            printf("movzb rax,al\n");
            printf("push rax\n");
        case ND_NEQU:
            printf("pop rax\n");
            printf("pop rdi\n");
            printf("cmp rax,rdi\n");
            printf("setne al\n");
            printf("movzb rax,al\n");
            printf("push rax\n");
        case ND_ESB:
            printf("pop rax\n");
            printf("pop rdi\n");
            printf("cmp rax,rdi\n");
            printf("setle al\n");
            printf("movzb rax,al\n");
            printf("push rax\n");
        case ND_SB:
            printf("pop rax\n");
            printf("pop rdi\n");
            printf("cmp rax,rdi\n");
            printf("setl al\n");
            printf("movzb rax,al\n");
            printf("push rax\n");
    }
}