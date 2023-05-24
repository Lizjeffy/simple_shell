#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */

char *without_comment(char *in)
{
	int a;
	int up_to;

	up_to = 0;
	a = 0;

	while (in[a])
	{
		if (in[a] == '#')
		{
			if (a == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[a - 1] == ' ' || in[a - 1] == '\t' || in[a - 1] == ';')
				up_to = a;
		}
	}
	a++;

	if (up_to != 0)
	{
		in = _realloc(in, a, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */

void shell_loop(data_shell *datash)
{
	int loop;
	int i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}