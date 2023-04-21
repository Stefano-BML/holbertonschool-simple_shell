#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Global variables */
extern char **environ;

/* Function prototypes */
void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);

#endif /* SHELL_H */
