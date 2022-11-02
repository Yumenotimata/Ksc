#include "mycc.h"

Token *doTokenize(char *code)
{
    Token *retToken = calloc(1,sizeof(Token));
    Token *opToken = calloc(1,sizeof(Token));
    opToken = retToken;
    while(*code)
    {
        if(isspace(*code))
        {
            code++;
            continue;
        }
        if(isdigit(*code))
        {
            opToken->next = makeNewNumToken(TK_NUM,strtol(code,&code,10));
            opToken = opToken->next; 
            continue;
        }
        if(*code == '=')
        {   code++;
            if(*code == '=')
            {
                code--;
                opToken->next = makeNewStrToken(TK_KIGOU,code);
                opToken = opToken->next;
                code+=2;
                continue;
            }else 
            {
                printf("'=' is not exist!");
                exit(1);
            }
            
        }

        if(*code == '!')
        {
            code++;
            if(*code == '=')
            {
                code--;
                opToken->next = makeNewStrToken(TK_KIGOU,code);
                opToken = opToken->next;
                code+=2;
                continue;
            }else 
            {
                printf("'=' is not exist !!\n'!' is need '='");
                exit(1);
            }
        }

        if(*code == '<')
        {
            code++;
            if(*code == '=')
            {
                code--;
                opToken->next = makeNewStrToken(TK_KIGOU,code);
                opToken = opToken->next;
                code+=2;
                printf("ok");
                continue;
            }
            if(isspace(*code) || isdigit(*code))
            {
                code--;
                printf("op");
                opToken->next = makeNewStrToken(TK_KIGOU,code);
                opToken = opToken->next;
                code++;
                continue;
            }else 
            {
                printf("errro\n");
                exit(1);
            }
        }
        if(*code == '>')
        {
            code++;
            if(*code == '=')
            {
                code--;
                opToken->next = makeNewStrToken(TK_KIGOU,code);
                opToken = opToken->next;
                code+=2;
                printf("ok");
                continue;
            }
            if(isspace(*code) || isdigit(*code))
            {
                code--;
                printf("op");
                opToken->next = makeNewStrToken(TK_KIGOU,code);
                opToken = opToken->next;
                code++;
                continue;
            }else 
            {
                printf("errro\n");
                exit(1);
            }
        }
        if(*code == '+')
        {
            opToken->next = makeNewStrToken(TK_KIGOU,code);
            opToken = opToken->next;
            code++;
            continue;
        }
        if(*code == '-')
        {
            opToken->next = makeNewStrToken(TK_KIGOU,code);
            opToken = opToken->next;
            code++;
            continue;
        }
         if(*code == '*')
        {
            opToken->next = makeNewStrToken(TK_KIGOU,code);
            opToken = opToken->next;
            code++;
            continue;
        }
        if(*code == '/')
        {
            opToken->next = makeNewStrToken(TK_KIGOU,code);
            opToken = opToken->next;
            code++;
            continue;
        }
        if(*code == '(')
        {
            opToken->next = makeNewStrToken(TK_KIGOU,code);
            opToken = opToken->next;
            code++;
            continue;
        }
        if(*code == ')')
        {
            opToken->next = makeNewStrToken(TK_KIGOU,code);
            opToken = opToken->next;
            code++;
            continue;
        }
    }
    opToken->next = makeEofToken();
    opToken = opToken->next;
    return retToken;
}

Token *makeNewStrToken(TokenKind kind,char *str)
{
    Token *retToken = calloc(1,sizeof(Token));
    retToken->kind = kind;
    retToken->str = str;
    return retToken;
}

Token *makeNewNumToken(TokenKind kind,int val)
{
    Token *retToken = calloc(1,sizeof(Token));
    retToken->kind = kind;
    retToken->val = val;
    return retToken;
}

Token *makeEofToken()
{
    Token *retToken = calloc(1,sizeof(Token));
    retToken->kind = TK_EOF;
    return retToken;
}