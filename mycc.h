#ifndef __H_MYCC_
#define __H_MYCC_

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
  
 typedef enum 
    {
        TK_KIGOU,
        TK_NUM,
        TK_EOF,
        TK_EQU,
        TK_NEQU,
        TK_SB,
        TK_ESB,
        TK_BS,
        TK_EBS,
    }TokenKind;

    typedef struct Token Token;

    struct Token
    {
        TokenKind kind;
        Token *next;
        char *str;
        int val;
    };

    typedef enum
    {
        ND_ADD,
        ND_SUB,
        ND_MUL,
        ND_DIV,
        ND_NUM,
        ND_EQU,
        ND_SB,
        ND_ESB,
        ND_BS,
        ND_EBS,
        ND_NEQU,
    }NodeKind;

    typedef struct Node Node;

    struct Node
    {
        NodeKind kind;
        int val;
        Node *lhs;
        Node *rhs;
    };
 
    Token *doTokenize(char *code);
    Token *makeNewStrToken(TokenKind kind,char *str);
    Token *makeNewNumToken(TokenKind kind,int val);
    Token *makeEofToken();

   
    Node *expr(Token **opToken);
    Node *mul(Token **opToken);
    Node *primary(Token **opToken);
    Node *unary(Token **opToken);
    Node *equality(Token **opToken);
    Node *relational(Token **opToken);
    Node *add(Token **opToken);

    bool ifKigou(Token **opToken,char *str);
    Node *makeNewNode(NodeKind kind,Node *lhs,Node *rhs);
    Node *makeNewNumNode(int val);

    void generateCode(Node *node);

#endif