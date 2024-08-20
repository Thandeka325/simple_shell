#include "shell.h"

/**
 * main - Entry point
 *
 * Return: Always 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1) /* Infinite loop for shell prompt */
	{
		printf("($) "); /* Display prompt */
		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (feof(stdin)) /* Handle EOF (Ctrl+D) */
			{
			free(line);
			exit(0); }
			else
			{
				perror("getline");
				continue; }}
		/* Remove trailing newline character */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		execute_command(line); } /* Execute the command */
	free(line);
	return (0);
}
