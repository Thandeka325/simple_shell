#include "shell.h"


/**
 * input_buffer - buffers chained commands
 * @info: Parameter struct
 * @buf: Pointer address of buffer
 * @len: Pointer address of length variable
 *
 * Return: Bytes read
 */
ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	ssize_t len_p = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
	#if USE_GETLINE
			r = getline(buffer, &len_p, stdin);
	#else
			r = _getline(info, buffer, &len_p);
	#endif
			if (r > 0)
			{
				if ((*buffer)[r - 1] == '\n')
				{
					(*buffer)[r - 1] = '\0';
					r--;
				}
				info->linecount_flag = 1;
				remove_comments(*buffer);
				build_history_list(info, *buffer, info->histcount++);
				{
					*len = r;
					info->cmd_buffer = buffer;
				}}}
	return (r);
}

/**
 * get_input - Gets a line minus the newline
 * @info: Parameter struct
 *
 * Return: Bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	size_t r = 0;
	char **buffer_p = &(info->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = input_buffer(info, &buffer, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		check_chain(info, buffer, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buffer_type = CMD_NORM;
		}
		*buffer_p = p;
		return (_strlen(p));
	}
	*buffer_p = buffer;
	return (r);
}
/**
 * read_buffer - Reads the buffer
 * @info: Parameter struct
 * @buffer: The buffer
 * @i: The size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
/**
 * _getline - Gets the next line of the input from STDIN
 * @info: Parameter struct
 * @ptr: Pointer to address buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buffer(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sigintHandler - Blocks ctrl-c
 * @sig_num: The signal number
 *
 * Return: Void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$");
	_putchar(BUFFER_FLUSH);
}
