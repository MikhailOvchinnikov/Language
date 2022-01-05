#include "language.h"

#include <stdio.h>
#include <stdlib.h>

const char* s = NULL;

void SyntaxError()
{
    printf("SyntaxError\n");
    exit(1);
}


int GetN()
{
    int val = 0;
    while ('0' <= *s && *s <= '9')
    {
        const char* old_s = s;
        val = val * 10 + (*s - '0');
        s++;
        if (old_s == s)
        {
            SyntaxError();
        }
    }
    return val;
}


int GetP()
{
    if (*s == '(')
    {
        s++;
        int val = GetE();
        Require(')');
        return val;
    }
    else
    {
        return GetN();
    }
}


int GetT()
{
    int val = GetP();
    while (*s == '*' || *s == '/')
    {
        char op = *s;
        s++;
        int val2 = GetP();
        if (op == '*')
        {
            val *= val2;
        }
        else
        {
            val /= val2;
        }
    }
    return val;
}


int GetE()
{
    int val = GetT();
    while (*s == '+' || *s == '-')
    {
        char op = *s;
        s++;
        int val2 = GetT();
        if (op == '+')
        {
            val += val2;
        }
        else
        {
            val -= val2;
        }
    }
    return val;
}


int GetG(const char* str)
{
    s = str;
    int val = GetE();
    Require('$');
    return val;
}


void Require(const char sym)
{
    if (*s == sym)
    {
        s++;
    }
    else
    {
        SyntaxError();
    }
}