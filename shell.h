#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
char *get_location(char *command);
void execmd(char **argv);

#endif
