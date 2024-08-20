#include "shell.h"


/**
 * find_command - Searches for the command in the PATH directorie
 * @command: The command to search for
 *
 * Return: The full path of the command if found, or NULL if not found
 */
char *find_command(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);/* Capy PATH to modify it */
	char *dir = path_copy;
	struct stat st;
	static char full_path[1024];

	while (dir && *dir != '\0')
	{
		char *next_colon = strchr(dir, ':');

		if (next_colon)
			*next_colon = '\0';

		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = next_colon ? next_colon + 1 : NULL;
	}
	free(path_copy);
	return (NULL);
}

/**
 * execute_external_command - Executes external commands
 * @argv: Array of command and argumentts
 */
void execute_external_command(char **argv)
{
	char *cmd_path = find_command(argv[0]);

	if (cmd_path == NULL)
	{
		fprintf(stderr, "./hsh: command not found: %s\n", argv[0]);
		return; }
	if (execve(cmd_path, argv, environ) == -1)
	{
		perror("./hsh"); }
}

/**
 * execute_command - Executes the command with arguments.
 * @command: The command to be executed
 */
void execute_command(char *command)
{
	char *argv[MAX_TOKENS];

	split_command(command, argv);
	if (argv[0] == NULL)
		return;
	if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "env") == 0)
	{
		execute_builtins(argv); }
	else
	{
		execute_external_command(argv);
	}
}
