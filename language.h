#pragma once


enum ElemType {
	NUM = 1,
	OP = 2
};


void SyntaxError();

float F(char* t_func);

float St();

float If();

float As();

float V(char* var);

Element* GetN();

float GetW(char* var);

float GetP();

Element* GetT();

float GetE();

float GetG(const char* str);

void Require(const char sym);