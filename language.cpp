#include "language.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EmptyPass while (strchr(" \t\r\n", *s)) s++;

const char* s = NULL;

typedef struct Var {
    char var[10] = {};
    float value = 0;
} Var;

typedef struct Element {
    int type = 0;
    int val = 0;
    Element* left;
    Element* right;
}Element;

Var vars[] = { "x", 10, "y", 15, "z", 100, "xyz", 300 };
const char func[][10] = { "sin", "cos" };

void SyntaxError()
{
    printf("SyntaxError\n");
    exit(1);
}


Element* CreateElement(int type, int val, Element* one, Element* two) {
    Element* element = (Element*)calloc(1, sizeof(Element));

    element->type = type;
    element->val = val;
    element->left = one;
    element->right = two;

    return element;
}


float F(char* t_func) {
    if (!strcmp(t_func, "sin")) {
        float val = GetE();
        return sin(val);
    }
    else if (!strcmp(t_func, "cos")) {
        float val = GetE();
        return cos(val);
    }
    else if (!strcmp(t_func, "ln")) {
        float val = GetE();
        return log(val);
    }
    else if (!strcmp(t_func, "exp")) {
        float val = GetE();
        return exp(val);
    }
    return 0;
}


float St() {
    const char* start = s;
    float answer = 0;
    if (answer = If()) {
        return answer;
    }
    s = start;
    if (answer = GetE()) {
        Require(';');
        return answer;
    }
    s = start;
    if(answer = As()){
        Require(';');
        return answer;
    }
    return answer;
}


float If() {
    char var[10] = {};
    float digit = 0;
    float answer = 0;
    GetW(var);
    EmptyPass;
    if (!strcmp(var, "if")) {
        digit = GetE();
        Require('{');
        if (digit)
            answer = St();
        else
            St();
        Require('}');
        GetW(var);
        EmptyPass;
        if (!strcmp(var, "else")) {
            Require('{');
            if (!digit) {
                answer = St();
            }
            else
                St();
            Require('}');
        }
    }
    return answer;
}


float As() {
    char var[10] = {};
    if (GetW(var)) {
        EmptyPass;
        if (*s == '=') {
            s++;
            float size = sizeof(vars) / sizeof(vars[0]);
            for (int i = 0; i < size; i++) {
                if (!strcmp(vars[i].var, var)) {
                    vars[i].value = GetE();
                    return vars[i].value;
                }
            }
        }
    }
    return 0;
}


float V(char* var) {
    EmptyPass;
    if (*s != '=') {
        float size = sizeof(vars) / sizeof(vars[0]);
        for (int i = 0; i < size; i++) {
            if (!strcmp(vars[i].var, var)) {
                return vars[i].value;
            }
        }
    }
    return 0;
}


Element* GetN()
{
    EmptyPass;
    float val = 0;
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
    return CreateElement(ElemType::NUM, val, NULL, NULL);
}


float GetW(char* var){
    if (!var)
        return 0;
    EmptyPass;
    int i = 0;
    while ('a' <= *s && *s <= 'z'){
        const char* old_s = s;
        var[i] = *s;
        s++;
        i++;
        if (old_s == s)
            SyntaxError();
    }
    if (i)
        return 1;
    else
        return 0;
}


float GetP()
{
    EmptyPass;
    float digit = 0;
    if (*s == '('){
        s++;
        digit = GetE();
        Require(')');
    }
    else if(!(digit = GetN())){
        char var[10] = {};
        GetW(var);
        if(!(digit = V(var)))
            digit = F(var);
    }
    return digit;
}


Element* GetT()
{
    float val = GetP();
    EmptyPass;
    if (*s == '*' || *s == '/')
    {
        char op = *s;
        s++;
        float val2 = GetP();
        if (op == '*')
        {
            val *= val2;
        }
        else
        {
            val /= val2;
        }
    }
    return CreateElement();
}


float GetE()
{
    float val = GetT();
    EmptyPass;
    if (*s == '+' || *s == '-')
    {
        char op = *s;
        s++;
        float val2 = GetT();
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


float GetG(const char* str)
{
    s = str;
    float val = 0;
    while (*s != '$') {
        val = St();
        EmptyPass;
    }
    printf("%f\n", vars[0].value);
    Require('$');
    return val;
}


void Require(const char sym)
{
    EmptyPass;
    if (*s == sym)
    {
        s++;
    }
    else
    {
        SyntaxError();
    }
}