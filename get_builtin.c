#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * get_builtin - builtin of the command
 * @cmd: command
 * Return: function pointer of the builtin command
 */

int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int a;

	for (a = 0; builtin[a].name; a++)
	{
		if (_strcmp(builtin[a].name, cmd) == 0)
			break;
	}

	return (builtin[a].f);
}
