#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * read_line - reads the input string
 *
 * @i_eof: return value of getline function
 * Return: input string
 */

char *read_line(int *i_eof)
{
	char *ip = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&ip, &bufsize, stdin);

	return (ip);
}
