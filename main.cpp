#include "tree.h"

#include "..\..\Sort_Onegin\Sort_Onegin\sort_text.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE* file = fopen("equation.txt", "rb");
	if (file == NULL)
	{
		fputs("Error file open\n", stderr);
		exit(1);
	}

	int syms = CountSymbols(file);
	char* text = (char*)calloc((syms + 1), sizeof(char));
	GetParametersFile(file, text, syms);

	fclose(file);
    printf("%d\n", GetG(text));
}
