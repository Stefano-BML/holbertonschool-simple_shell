#include "shell.h"

int tok_num(char *str, char *delims)
{
	int tokTotal = 0, i, lineLen = 0;

	lineLen = _strlen(str);
	for (i = 0; i < lineLen; i++)
	{
		printf("%s\n", str);
                printf ("%c\n", str[i]);
		if (str[i] && str[i] != delims[0] && str[i] != delims[1])
		{
			tokTotal++;
			i += substrLen(str + i, delims);
		}
	}
	return (tokTotal);
}

int main(int argc, char *argv[])
{
	char *line = "hola como estas";
	char *delim = " \n\0\t\r";
	int num = tok_num(line, delim);
	return (0);
}
