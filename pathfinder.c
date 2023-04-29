#include "shell.h"

char **path_locate(char *envvar);
char **path_tok(char *path);
char *check_paths(char *command);

/**
 * path_locate - is a function that yoinks path from env
 * @envvar: env var array in
 * Return: array of path strs
 */
char **path_locate(char *envvar)
{
	unsigned int i = 0;

	if (!environ)
		return (NULL);
	if (!(*environ))
		return (NULL);
	if (!(**environ))
		return (NULL);
	
	for (; environ[i]; i++)
	{
		if (_strncmp(envvar, environ[i], _strlen(envvar)) == 0)
		{
			pathArr = path_tok(environ[i]);
			return (pathArr);
		}
	}
	return (pathArr);
}

/**
 * path_tok - is a function that supplies path info to tokenizer
 * @path: PATH from inherited env
 * Return: tokenized PATH
 */
char **path_tok(char *path)
{
	char *separator = ":";

	pathArr = tokstr(path, separator);
	pathArr[0] += 5;
	return (pathArr);
}

/**
 * check_paths - checks pathArr against command[0]
 * @command: first tok of command array
 * Return: composite path to command if one exists
 */
char *check_paths(char *command)
{
	unsigned int i = 0, pathLen = 0;
	struct stat s;
	char *cmpPath = NULL;

	if (stat(command, &s) == 0)
		return (command);
	
	pathArr = path_locate("PATH=");
	
	if (!pathArr)
		return (command);

	if (command[0] != '/' && command[0] != '.')
	{
		for (; pathArr[i]; i++)
		{
			pathLen = (_strlen(pathArr[i]) + _strlen(command) + 2);
			cmpPath = malloc(sizeof(char) * pathLen);
			_strcpy(cmpPath, pathArr[i]);
			_strcat(cmpPath, "/");
			_strcat(cmpPath, command);
			if (stat(cmpPath, &s) == 0)
			{
				free_path(pathArr);
				return (cmpPath);
			}
			free(cmpPath);
		}
	}
	free_path(pathArr);
	return (command);
}
