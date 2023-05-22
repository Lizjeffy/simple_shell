#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * cd_dot - changes to parent directory
 *
 * @datash: data relevant
 */
void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *cpwd;
	char *cp_strtok_pwd;
	char *dir;

	getcwd(pwd, sizeof(pwd));
	cpwd = _strdup(pwd);
	set_env("OLDPWD", cpwd, datash);
	dir = datash->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cpwd, datash);
		free(cpwd);
		return;
	}
	if (_strcmp("/", cpwd) == 0)
	{
		free(cpwd);
		return;
	}
	cp_strtok_pwd = cpwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cpwd);
}

/**
 * cd_to - changes to directory given by the user
 *
 * @datash: data relevant
 */

void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *cpwd;
	char *cp_dir;
	char *dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cpwd = _strdup(pwd);
	set_env("OLDPWD", cpwd, datash);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, datash);

	free(cpwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to previous directory
 *
 * @datash: data relevant
 */

void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_oldpwd;
	char *cpwd;
	char *cp_oldpwd;
	char *p_pwd;

	getcwd(pwd, sizeof(pwd));
	cpwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cpwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cpwd, datash);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cpwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	p_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cpwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 */
void cd_to_home(data_shell *datash)
{
	char *p_pwd;
	char *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
