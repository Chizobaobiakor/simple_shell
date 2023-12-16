#include <shell.h>

/**
 * rev_string - reversal of a string
 * @str: the string itself
 * lucy
 * Return: void
 */
void rev_string(char *str)
{
	int z, len;
	char tmp;

	len = 0;
	while (str[len] != '\0')
		len++;
	len--;
	for (z = 0; z < len; z++, len--)
	{
		tmp = str[z];
		str[z] = str[len];
		str[len] = tmp;
	}
}

/**
 * _itoa - conversion of the string
 * @command_num: number undergoing  conversion
 *
 * Return: the integer converted
 */
char *_itoa(size_t command_num)
{
	char *str = malloc(sizeof(char) * (32 + 1));
	int z = 0;

	do {
		str[z++] = command_num % 10 + '0';
		command_num /= 10;
	} while (command_num > 0);
	str[z] = '\0';
	rev_string(str);

	return (str);
}
