#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>

extern char **environ;
int _putchar(char c);
void prompt(void);
void read_command(char *buffer, size_t size);
void execute_command(char *command);



#endif /* SHELL_H */
