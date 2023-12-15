#include "shell.h"

/**
 * builtins - Prints all environment variables
 * @argv: Command line arguments
 * @env: Environment variables
 * @token_array: Tokenize user input
 * Return: status 1 on successfully finding command or -1 otherwise
 */

int handle_builtins(char **argv, char **env, char **token_array)
{
	int check = -1, z = 0;

	Built_in cd_s = {"cd", cd_func};
	Built_in exit_s = {"exit", exit_func};
	Built_in env_s = {"env", env_func};

	Built_in *builtin_ptr[3];

	builtin_ptr[0] = &cd_s;
	builtin_ptr[1] = &exit_s;
	builtin_ptr[2] = &env_s;

	while (z < 3)
	{
		if (_strcmp(token_array[0], builtin_ptr[z]->cmd) == 0)
		{
			builtin_ptr[i]->fnc_cmd(argv, env, token_array);
			check = 1;
			break;
		}
		z++;
	}

	return (check);
}
/**
 * cd_func - Builtin function that changes current directory
 * @argv: Argument vector from command line
 * @env: Environment variables
 * @token_array: Array of user entry token
 */

void cd_func(char **argv, char **env, char **token_array)
{
	char *dir = NULL;
	size_t size = 0;
	char *old_pwd = getenv("OLDPWD");

	(void)env;

	if (token_array[1] != NULL)
	{
		if (token_array[1][0] == '-')
		{
			chdir(old_pwd);
		}
		else if (chdir(token_array[1]) == -1)
		{
			err_msg(2, cmd_count, argv[0], "can't cd to", token_array[1]);
		}
		return;
	}
	if (chdir(getcwd(dir, size)) == -1)
	{
		err_msg(2, cmd_count, argv[0], "can't cd to", token_array[0]);
	}
	free(dir); /*Cause mem leak*/
}

/**
 * env_func - Builtin function prints the environment
 * @argv: Argument vector from command line
 * @env: Environment variables
 * @token_array: Array of user entry token
 */

void env_func(char **argv, char **env, char **token_array)
{
	int z = 0, y = 0;

	(void)argv;
	(void)token_array;

	while (env[z])
	{
		while (env[z][y])
		{
			write(1, &env[z][y], 1);
			y++;
		}
		y = 0;
		z++;
		write(1, "\n", 1);
	}
}
