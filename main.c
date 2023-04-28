#include "shell.h"

/*<<<<<<< HEAD*/
char **pathArr;
int ret_val = 0;
int hist = 0;
char *pName;
/*=======*/
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

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (!isatty(STDIN_FILENO))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		perror("read_line");
		return (NULL);
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
	int size = 2;

	args = malloc(sizeof(char *) * size);
	if (args == NULL)
	{
		perror("split_line");
		return (NULL);
	}

	token = strtok(line, " \t\n\r");
	args[i] = token;

	while (token != NULL)
	{
		i++;
		if (i >= size)
		{
			args = realloc(args, sizeof(char *) * (i + 2));
			if (args == NULL)
			{
				perror("split_line");
				return (NULL);
			}
		}

		token = strtok(NULL, " \t\n\r");
		args[i] = token;

	}
	args[i] = NULL;
	return (args);
}
/*>>>>>>> 5ea6b927a6fc6c8f35e8b4f4a75b201891ca5497*/

/**
 * main - Entry point for ghost
 * @argc: arg count
 * @argv: array of input arg strings
 * Return: TBD
 */
int main(int argc, char *argv[])
{
	char *line = NULL, *thePath = NULL, **command = NULL;
	size_t llen;

	signal(SIGINT, sig_stop);
	pName = argv[0];
	if (argc != 1)
		exit(EXIT_FAILURE);
	while (1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		if (getline(&line, &llen, stdin) < 0)
			free_exit(line);
		cleanstr(line);
		if (tok_num(line, " ") <= 0)
			continue;
		command = get_input(line);
		if (runBuiltIn(command, line) >= 0)
			continue;
		thePath = check_paths(command[0]);
		if (access(thePath, X_OK) != 0)
		{
			if (access((thePath), F_OK) == 0)
				ret_val = 126;
			else
				ret_val = 127;
			errorHand(hist, command[0], pName);
			free_tokens(command);
			continue;
		}
		ret_val = forktime(command, thePath);
	}
	return (0);
}
