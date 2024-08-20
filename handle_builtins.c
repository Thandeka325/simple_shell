#include "shell.h"

/**
 * execute_builtins- Handles built-in commands (exit,env).
 * @argv: Array of arguments
 */
void execute_builtins(char **argv)
{
	if (strcmp(argv[0], "exit") == 0)
	{
		int status = 0; /* Default exit status */

		if (argv[1] != NULL)
		{
			status = atoi(argv[1]);/* Convert argument to integer */
		}
		exit(status);/* Exit the shell with the given status */
	}

	if (strcmp(argv[0], "env") == 0)
	{
		char **env;/*Declare the variable before the loop */

		for (env = environ; *env; env++)
		{
			printf("%s\n", *env);
		}
	}
}
