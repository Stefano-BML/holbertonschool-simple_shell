#include "shell.h"

extern char **environ;

/**
 * main - Entry point for the shell programs
 * @argc: Number of arguments passed to the program
 * @argv: Array of arguments passed to the program
 *
 * Return: Always 0
 */

int main(int argc, char **argv)
{
        char *line = NULL;
        char **args = NULL;
        int status;
	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO))
	{
		do {
			prompt();
			line = read_line();
			args = split_line(line);
			status = execute(args);
			
			free(line);
			free(args);
		} while (status);
	}
	else
	{
		do {
			line = read_line();
			args = split_line(line);
			status = execute(args);

			free(line);
			free(args);
		} while (status);
	}

	return (0);
}


/**
 * prompt - Prints a prompt for the user
 */
void prompt(void)
{
		printf("$ ");
		fflush(stdout);
}

/**
 * read_line - Reads a line of input from the user
 *
 * Return: A pointer to the line of input, or NULL if an error occurs
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1) {
		if (!isatty(STDIN_FILENO)){
			exit(EXIT_FAILURE);
		}
		perror("read_line");
		exit(EXIT_FAILURE);
	}

	return (line);
}

/**
 * split_line - Splits a line of input into an array of arguments
 * @line: The line of input to split
 *
 * Return: An array of arguments, or NULL if an error occurs
 */
char **split_line(char *line)
{
	char **args = NULL;
	char *token = NULL;
	int i = 0;

	args = malloc(sizeof(char *) * 2);
	if (args == NULL) {
		perror("split_line");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\n\r");
	args[i] = token;

	while (token != NULL) {
		i++;
		args = realloc(args, sizeof(char *) * (i + 2));
		if (args == NULL) {
			perror("split_line");
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, " \t\n\r");
		args[i] = token;
	}

	return (args);
}

/**
 * execute - Executes a command with the given arguments
 * @args: The arguments for the command
 *
 * Return: 1 if the shell should continue running, 0 otherwise
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL) {
		return (1);
	}

	if (strcmp(args[0], "exit") == 0) {
		return (0);
	}

	pid = fork();
	if (pid == -1) {
		perror("execute");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		/* Child process */
		if (execve(args[0], args, environ) == -1) {
			perror("execute");
			exit(EXIT_FAILURE);
		}
	} else {
		/* Parent process */
		wait(&status);
	}
	
	return (1);
}
