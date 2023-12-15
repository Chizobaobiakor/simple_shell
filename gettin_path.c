#include "shell.h"
#include <stdlib.h>

/**
 * get_path - This returns a pointer from the environmental variables
 * to a path variable of the system
 * @env: Environmental Variable of the Path
 * Return: Char *pointer to the paths
 */

char *get_path(char **env)
{
	char *path = NULL;
	int z = 0;

	while (env[z])
	{
		if (_strstr(env[z], "PATH") && env[z][0] == 'P' && env[z][4] == '=')
		{
			path = env[z];
			break;
		}
		z++;
	}
	if (path != NULL)
	{
		for (z = 0; z < 8; z++)
			path++;
	}

	return (path);
}
