#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * exec_line - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */

int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	builtin = get_builtin(datash->args[0]);

	if (datash->args[0] == NULL)
		return (1);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
