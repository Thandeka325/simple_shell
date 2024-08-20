#include "shell.h"

static ssize_t fill_buffer(char *buffer,size_t *buffer_size,
		FILE *stream);
static ssize_t extract_line(char **lineptr, size_t *n,
		char *buffer, size_t *buffer_pos, size_t buffer_size);

/**
 * custom_getline - Custom implementation of getline.
 * @lineptr: Pointer to the buffer where the line will be stored
 * @n: Pointer to the size of he buffer
 * @stream: Input stream (usually stdin)
 *
 * Return: The number of characters read, or -1 on failure
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_pos, buffer_size;
	ssize_t line_len = 0;

	if (!lineptr || !n || !stream)
		return (-1);
	if (*lineptr == NULL)
	{
		*n = BUFFER_SIZE;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			line_len = fill_buffer(buffer, &buffer_size, stream);
			if (line_len == -1)
				return (-1);
			buffer_pos = 0;
		}
		line_len = extract_line(lineptr, n, buffer, &buffer_pos, buffer_size);
		if (line_len != 0)
			return (line_len); }
}

/**
 * fill_buffer - Fills the buffer with data from the input stream.
 * @buffer: The buffer to be filled
 * @buffer_size: Pointer to the size of the data in the buffer
 * @stream: Input stream (usually stdin)
 *
 * Return: 0 on success, or -1 on failure
 */
static ssize_t fill_buffer(char *buffer, size_t *buffer_size,
		FILE *stream)
{
	*buffer_size = read(fileno(stream), buffer, BUFFER_SIZE);

	if (*buffer_size == 0)
		return (-1);
	else if (*buffer_size == (size_t)-1)
		return (-1);
	return (0);
}

/**
 * extract_line - Ectracts a line from the buffer
 * @lineptr: Pointer to the buffer where line will be stored
 * @n: Pointer to the size of the buffer
 * @buffer: The buffer to extract the line from
 * @buffer_pos: Pointer to the current position in the buffer
 * @buffer_size: The siize of data in the buffer
 *
 * Return: The number oof characters read, or 0 if more data is needed
 */
static ssize_t extract_line(char **lineptr, size_t *n, char *buffer,
		size_t *buffer_pos, size_t buffer_size)
{
	size_t line_len = 0;
	char *new_line;

	while (*buffer_pos < buffer_size)
	{
		if (line_len >= *n - 1)
		{
			*n *= 2;
			new_line = realloc(*lineptr, *n);
			if (!new_line)
				return (-1);
			*lineptr = new_line;
		}
		(*lineptr)[line_len++] = buffer[(*buffer_pos)++];

		if ((*lineptr)[line_len - 1] == '\n')
		{
			(*lineptr)[line_len] = '\0';
			return (line_len);
		}
	}
	return (0);
}

