#include "shell.h"

extern char **environ; /* External variable to access the env */

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
	char *dir = strtok(path_copy, ":");
	struct stat st;
	static char full_path[1024];

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
/**
 * execute_command - Executes the command with arguments
 * @command: The command to be executed
 */
void execute_command(char *command)
{
	char *argv[100];/* Array to hold command & arguments */
	char *token;
	char *cmd_path;

	int i = 0;

	/* Tokenize the command line into command and arguments */
	token = strtok(command, " ");

	while (token != NULL && i < 99)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;/* NULL-terminate the array */
	/* Check if the command is "exit" */
	if (strcmp(argv[0], "exit") == 0)
	{
		exit(0); } /* Exit the shell */
	/* check if the command is "env" */
	if (strcmp(argv[0], "env") == 0)
	{
		char **env = environ;

		while (*env)
		{
			printf("%s\n", *env);/* Prints each env variable */
			env++; }
		return; }
	/* Check if the command exists in Path */
	cmd_path = find_command(argv[0]);

	if (cmd_path == NULL)
	{
		fprintf(stderr, ".hsh: command not found: %s\n", argv[0]);
		return; }

	if (execve(cmd_path, argv, NULL) == -1)
	{
		perror("./hsh"); } /* prints error if command fails */
}
