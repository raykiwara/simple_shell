#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char **tokeniser(char *buffer_cpy);
void execute(char **array);
/**
 * main - Prog entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	char *buffer, *buffer_cpy, **array;
	size_t n;
	int length;

	buffer = NULL;
	n = 0;

	printf("#cisfun$ ");
	while (getline(&buffer, &n, stdin) != EOF)
	{
		length = strlen(buffer);
		buffer[length - 1] = '\0';
		buffer_cpy = strdup(buffer);
		array = tokeniser(buffer_cpy);
		execute(array);
		free(buffer_cpy);
		free(array);
		printf("#cisfun$ ");
	}
	printf("\n");
	free(buffer);

	return (0);
}
/**
 * tokeniser - splits a string into tokens
 *
 * @buffer_cpy: copy of the string
 * Return: array of the tokens
 */
char **tokeniser(char *buffer_cpy)
{
	char **array, *token, *delim;
	int j;

	delim = " ";

	array = malloc(sizeof(char *) * 1024);

	j = 0;

	token = strtok(buffer_cpy, delim);
	while (token)
	{
		array[j] = token;
		token = strtok(NULL, delim);
		j++;
	}
	array[j] = NULL;

	return (array);
}
/**
 * execute - calls execve
 *
 * @array: arguments
 */
void execute(char **array)
{
	pid_t child;

	child = fork();

	if (child == -1)
		printf("Failed to fork\n");

	if (child == 0)
	{
		if (execve(array[0], array, NULL) == -1)
			perror("Error");
	}
	else
		wait(NULL);
}
