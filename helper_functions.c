#include "shell.h"

/**
 * split_command - Splits a command string into an array of tokens.
 * @command: The command string to be split
 * @argv: Array to hold the command and arguments
 */
void split_command(char *command, char **argv)
{
	int i = 0;
	char *start = command;
	char *end;

	while (*start && i < MAX_TOKENS - 1)
	{
		while (*start == ' ') /* Skip leading spaces */
			start++;
		/*find the end of the token */
		end = start;

		while (*end && *end != ' ')
			end++;
		if (end > start)
		{
			argv[i++] = start; /* Store the token */
			if (*end)
				*end = '\0';
			start = end + 1; }}
	argv[i] = NULL;
}
