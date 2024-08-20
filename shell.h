#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>

#define BUFFER_SIZE 11024
#define MAX_TOKENS 100

extern char **environ;
int _putchar(char c);
void prompt(void);
void read_command(char *buffer, size_t size);
void execute_command(char *command);
void execute_builtins(char **argv);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void split_command(char *command, char **argv);
char *find_command(char *command);
void execute_external_coommand(char **argv);


#endif /* SHELL_H */
