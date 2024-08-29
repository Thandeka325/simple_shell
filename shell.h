#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stddef.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


/* Defining variables and parameters */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE	0
#define USE_STRTOK	0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - Singly linked list
 * @num: The number field
 * @str: A string
 * @next: Points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudoo-arguements to pass into the function,
 * allowing uniform prototype for fuction pointer struct
 * @arg: A string generated from getline containing arguments
 * @argv: An array of strings generated from arg
 * @path: A string path for the current command
 * @argc: The argument count
 * @line_count: The error count
 * @err_num: The error code for exits()
 * @linecount_flag: If on count this line is an input
 * @fname: The program filename
 * @env: Linked list local copy of environ
 * @environ: Custom modified copy of environ from env
 * @history: The history node
 * @alias: The alias node
 * @env_changed: On if environ was changed
 * @status: The return status of the last executed command
 * @cmd_buffer: The address pointer to cmd_buffer
 * @cmd_buffer_type: CMD_type ||, &&, ;
 * @readfd: The field descriptor to read read input from
 * @histcount: The history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	
	char **cmd_buffer;
	int cmd_buffer_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, \
		0, 0, NULL, 0, 0, 0}

/**
 * struct builtin - Contains a builtin string and related function
 * @type: The builtin command flag
 * @func: The function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function prototypes */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int loophsh(char **);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
int _eputchar(char);
void _eputs(char *);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
int _putchar(char);
void _puts(char *);
char *_strdup(const char *);
char *_strcpy(char *, char *);
char *_starts_with(const char *, const char *);
int _strcmp(char *, char *);
int _strlen(char *);
char *_strcat(char *, char *);
char **strtow2(char *, char);
char **strtow(char *, char *);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
char *_memset(char *, char, unsigned int);
int bfree(void **);
int _atoi(char *);
int _isalpha(int);
int is_delim(char, char *);
int interactive(info_t *);
void remove_comments(char *);
char *convert_number(long int, int, int);
int print_d(int, int);
void print_error(info_t *, char *);
int _erratoi(char *);
int _ownhelp(info_t *);
int _owncd(info_t *);
int _ownexit(info_t *);
int _alias(info_t *);
int _history(info_t *);
void sigintHandler(int);
int _getline(info_t *, char **);
ssize_t get_input(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);
void clear_info(info_t *);
int populate_env_list(info_t *);
int _ownunsetenv(info_t *);
int _ownsetenv(info_t *);
int _ownenv(info_t *);
char *_getenv(info_t *, const char *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);
char **get_environ(info_t *);
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *buffer, int linecount);
int read_history(info_t *info);
int write_history(info_t *info);
char *get_history_file(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);


#endif /* SHELL_H */
