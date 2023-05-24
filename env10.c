#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * cmp_env_name - compares environment variables names with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */

int cmp_env_name(const char *nenv, const char *name)
{
	int a;

	a = 0;

	while (nenv[i] != '=')
	{
		if (nenv[a] != name[a])
		{
			return (0);
		}
	}
	a++;

	return (a + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found. In other case, returns NULL.
 */

char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int a = 0, m;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	m = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */

	while (_environ[a])
	{
		/* If name and env are equal */
		m = cmp_env_name(_environ[a], name);
		if (m)
		{
			ptr_env = _environ[a];
			break;
		}
	}
	a++;

	return (ptr_env + m);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */

int _env(data_shell *datash)
{
	int x = 0, y;

	while (datash->_environ[x])
	{
		for (y = 0; datash->_environ[x][y]; y++)
			;

		write(STDOUT_FILENO, datash->_environ[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	x++;
	datash->status = 0;

	return (1);
}
