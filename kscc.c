#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>


typedef enum{
    TOK_KIGOU,
    TOK_NUM,
    TOK_EOS,
}TokenKind;
typedef struct Token Token;
struct Token{
    TokenKind kind;
    Token *next;
    int val;
    char *str;
};
Token *token;


typedef enum
{
    NOD_ADD,
    NOD_SUB,
    NOD_MUL,
    NOD_DIV,
    NOD_NUM,
}NodeKind;
typedef struct Node Node;
struct Node
{
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    int val;
};


void error(char *msg)
{
    printf("%s",msg);
    exit(1);
}

bool consume(char op)
{
    if(token->kind != TOK_KIGOU ||token->str[0] != op)
    {
        return false;
    }
    token = token->next;
    return true;
}

void expect(char op)
{
    if(token->kind != TOK_KIGOU || token->str[0]!=op)
    {
        printf("%cではありません。",op);
        exit(1);
    }
    token = token->next;
}

int expect_number()
{
    if(token->kind != TOK_NUM)
    {
        printf("数ではありません");
        exit(1);
    }
    int val = token->val;
    token = token->next;
    return val;
}

bool at_eos()
{
    return token->kind == TOK_EOS;
}

Token *new_token(TokenKind kind,Token *cur,char *str)
{
    Token *tok = calloc(1,sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    cur->next = tok;
    return tok;
}

Token *tokenize(char *text)
{
    Token head;
    head.next = NULL;
    Token *cur = &head;

    while(*text)
    {
        if(isspace(*text))
        {
            text++;
            continue;
        }

        if(*text == '+'||*text == '-')
        {
            cur = new_token(TOK_KIGOU,cur,text);
            text++;
            continue;
        }
         if(*text == '*'||*text == '/')
        {
            cur = new_token(TOK_KIGOU,cur,text);
            text++;
            continue;
        }

         if(*text == '('||*text == ')')
        {
            cur = new_token(TOK_KIGOU,cur,text);
            text++;
            continue;
        }

        if(isdigit(*text))
        {
            cur = new_token(TOK_NUM,cur,text);
            cur->val = strtol(text,&text,10);
            continue;
        }
        printf("トークナイズできません。");
        exit(1);
    }

    new_token(TOK_EOS,cur,text);
    return head.next;
}


Node *new_node(NodeKind kind,Node *lhs,Node *rhs)
{
    Node *node = calloc(1,sizeof(Node));
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_node_num(int val)
{
    Node *node = calloc(1,sizeof(Node));
    node->kind = NOD_NUM;
    node->val = val;
    return node;
}

Node *expr();
Node *mul();
Node *primary();

Node *primary()
{
    if(consume('('))
    {
        Node *node = expr();
        expect(')');
        return node;
    }

    return new_node_num(expect_number());
}

Node *mul()
{
    Node *node = primary();

    for(;;)
    {
        if(consume('*'))
        {
            node = new_node(NOD_MUL,node,primary());
        }else if(consume('/'))
        {
            node = new_node(NOD_DIV,node,primary());
        }else 
        {
            return node;
        }
    }
}

Node *expr()
{
    Node *node = mul();

    for(;;)
    {
        if(consume('+'))
        {
            node = new_node(NOD_ADD,node,mul());
        }else if(consume('-'))
        {
            node = new_node(NOD_SUB,node,mul());
        }else
        {
            return node;
        }
    }
}

void gen(Node *node) {
  if (node->kind == NOD_NUM) {
    printf("  push %d\n", node->val);
    return;
  }

  gen(node->lhs);
  gen(node->rhs);

  printf("  pop rdi\n");
  printf("  pop rax\n");

  switch (node->kind) {
  case NOD_ADD:
    printf("  add rax, rdi\n");
    break;
  case NOD_SUB:
    printf("  sub rax, rdi\n");
    break;
  case NOD_MUL:
    printf("  imul rax, rdi\n");
    break;
  case NOD_DIV:
    printf("  cqo\n");
    printf("  idiv rdi\n");
    break;
  }

  printf("  push rax\n");
}

int main(int argc,char *argv[])
{
    char *text = "2*3+4-(4*(4/3)/6*5)";
    token = tokenize(text);
    char *user_input;
    user_input = text;
    Node *node = expr();

    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
    //printf("    mov rax, %ld\n", expect_number());

    gen(node);
   
    printf("  ret\n");

}