#include "shell.h"

/**
 * _eputs - Prints an input string
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
/**
 * _eputchar - Writes the character c to stderr
 * @c: The character to print
 *
 * Return: 1 on success, -1 on error, and errno is set
 */
int _eputchar(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}
/**
 * _putfd - Writes the character c to a given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: 1 on success, -1 on error, and errno is set
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}
/**
 * _putsfd - Prints an input string
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
