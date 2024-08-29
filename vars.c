#include "shell.h"

/**
 * is_chain - Test if current char in buffer is a chain delimeter
 * @info: The parameter struct
 * @buffer: The char buffer
 * @p: The address of current position in buffer
 *
 * Return: 1 if chain delimeter, otherwisw 0
 */
int is_chain(info_t *info, char *buffer, size_t *p)
{
	size_t j = *p;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buffer_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		info->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Checks if chaining should continue based on last status
 * @info: The paeameter struct
 * @buffer: The char buffer
 * @p: Address of current position in buffer
 * @i: Starting position in buffer
 * @len: Length of buffer
 *
 * Return: void
 */
void check_chain(info_t *info, char *buffer, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buffer_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buffer_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * replace_alias - Replace an alias in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replicated, otherwise 0
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces vars in tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Replaces string
 * @old: Address of old string
 * @new: The new string
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
