#include "shell.h"

char **tokstr(char *line, char *delims)
{
    char **tokenStorage;
    int i, j = 0, k, tokTotal, ssLen = 0;

    if (!line)
        return (NULL);
    if (!(*line))
        return (NULL);
    tokTotal = tok_num(line, delims);
    tokenStorage = malloc(sizeof(char *) * (tokTotal + 1));
    for (i = 0; i < tokTotal; i++)
    {
        while (line[j] == *delims || line[j] == delims[1])
            j++;
        ssLen = substrLen(line + j, delims);
        tokenStorage[i] = malloc(sizeof(char) * (ssLen + 1));
        for (k = 0; k < ssLen; k++, j++)
            tokenStorage[i][k] = line[j];
        tokenStorage[i][k] = '\0';
    }
    tokenStorage[i] = NULL;
    return (tokenStorage);
}

int main(int argc, char *argv[])
{
        char *line = "hola como estas";
        char *delim = " \n\0\t\r";
        char **almacen = tokstr(line, delim);
        int i;
        for (i = 0; i < tok_num(line,delim); i++)
          printf("%s ", almacen[i]);
          
        return (0);
}
