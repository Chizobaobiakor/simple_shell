#include "shell.h"

/**
 * main - A program that emulates the Thompson Shell.
 * @argc: Argument Counter
 * @argv: Argument Variables - Null-terminated array of strings
 * @env: Environment variables
 * Return: Always (0) on success
 */

int main(int argc, char **argv, char **env)
{
	int mode = 0;

	cmd_count = 1;
	(void)argc;

	if (isatty(0) == 1)
		mode = 1;

	errno = 0;

	while (1)
	{
		if (mode == 1)
		{
			write(1, "$ ", 2);
		}

		handle_interactions(argv, env, &cmd_count, &mode);
		cmd_count++;
	}

	return (errno);
}

/**
 * free_array_tokens - frees an array of strings
 * @array_tokens: Argument pointer to be freed
 * Return: Void;
 */

void free_array_tokens(char **array_tokens)
{
	int z = 0;

	while (array_tokens[z] != NULL)
	{
		free(array_tokens[z]);
		z++;
	}

	free(array_tokens);
}
