#include "shell.h"

/**
 * **strtow - spliting string into words.
 * Repeat delimiters are ignored
 * @str: the inputed string
 * @d: the delimeter of the string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int z, y, r, t, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (z = 0; str[z] != '\0'; z++)
		if (!is_delim(str[z], d) && (is_delim(str[z + 1], d) || !str[z + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (z = 0, y = 0; y < numwords; y++)
	{
		while (is_delim(str[z], d))
			z++;
		r = 0;
		while (!is_delim(str[z + r], d) && str[z + r])
			r++;
		s[y] = malloc((r + 1) * sizeof(char));
		if (!s[y])
		{
			for (r = 0; r < y; r++)
				free(s[r]);
			free(s);
			return (NULL);
		}
		for (t = 0; t < r; t++)
			s[y][t] = str[z++];
		s[y][t] = 0;
	}
	s[y] = NULL;
	return (s);
}

/**
 * **strtow2 - spliting string into words
 * @str: the inputed string
 * @d: the delimeter
 * Return: a pointer of an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int z, y, r, t, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (z = 0; str[z] != '\0'; z++)
		if ((str[z] != d && str[z + 1] == d) ||
				(str[z] != d && !str[z + 1]) || str[z + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (z = 0, y = 0; y < numwords; y++)
	{
		while (str[z] == d && str[z] != d)
			z++;
		r = 0;
		while (str[z + r] != d && str[z + r] && str[z + r] != d)
			r++;
		s[y] = malloc((r + 1) * sizeof(char));
		if (!s[y])
		{
			for (r = 0; r < y; r++)
				free(s[r]);
			free(s);
			return (NULL);
		}
		for (t = 0; t < r; t++)
			s[y][t] = str[z++];
		s[y][t] = 0;
	}
	s[y] = NULL;
	return (s);
}
