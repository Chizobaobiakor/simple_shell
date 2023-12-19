#include <shell.h>
/**
 * input_buf - buffering chained commands
 * @info: parameter of the struct
 * @buf: buffer address
 * @len: len variable address
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t g  = 0;
	size_t len_x = 0;

	if (!*len)
		free(*buf);
	*buf = NULL;
	signal(SIGINT, sigintHandler);
#if USE_GETLINE
	g = getline(buf, &len_x, stdin);
#else
	g = _getline(info, buf, &len_x);
#endif
	if (g > 0)
	{
		if ((*buf)[g - 1] == '\n')
		{
			(*buf)[g - 1] = '\0'; /* remove trailing newline */
			g--;
		}
		info->linecount_flag = 1;
		remove_comments(*buf);
		build_history_list(info, *buf, info->histcount++);
		/* if (_strchr(*buf, ';')) is this a command chain? */
		{
			*len = g;
			info->cmd_buf = buf;
		}
	}
}
return (g);
}

/**
 * get_input - getting a line that minus the newline
 * @info: parameter of the struct
 *
 * Return: bytes to be read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t z, y, len;
	ssize_t g = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	g = input_buf(info, &buf, &len);
	if (g == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		y = z; /* init new iterator to current buf position */
		p = buf + z; /* get pointer for return */

		check_chain(info, buf, &y, z, len);
		while (y < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		z = y + 1;
		if (z >= len)
		{
			z = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (g); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *z)
{
	ssize_t g = 0;

	if (*z)
		return (0);
	g = read(info->readfd, buf, READ_BUF_SIZE);
	if (g >= 0)
		*z = g;
	return (g);
}

/**
 * _getline - getting the next line of input from STDIN
 * @info: parameter of the struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t z, len;
	size_t h;
	ssize_t g = 0, d = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		d = *length;
	if (z == len)
		z = len = 0;

	d = read_buf(info, buf, &len);
	if (g == -1 || (g == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	h = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, d, d ? d + h : h + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (d)
		_strncat(new_p, buf + z, h - z);
	else
		_strncpy(new_p, buf + z, h - z + 1);

	d += h - z;
	z = h;
	p = new_p;

	if (length)
		*length = d;
	*ptr = p;
	return (d);
}

/**
 * sigintHandler - blocking of ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
