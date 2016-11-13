#include "get_next_line.h"

static unsigned int	check_line(char *buf)
{
		unsigned int i;

		i = 0;
		while (buf[i] != '\0')
		{
				if (buf[i] == '\n')
				{
						buf[i] = '\0';
						return (i + 1);
				}
				i++;
		}
		return (i);
}

static void			join_buf(char **buf2, char **buf)
{
		char	*tmp;
		char	*tmp2;

		tmp = NULL;
		tmp2 = NULL;
		if (*buf2 && **buf2)
		{
				tmp2 = ft_strdup(*buf2);
				if (*buf)
				{
						tmp = ft_strdup(*buf);
						free(*buf);
				}
				*buf = ft_strjoin(tmp, tmp2);
				if (tmp)
						free(tmp);
				if (tmp2)
						free(tmp2);
		}
}

static int			return_line(char **buf, char **buf2, char **line)
{
		unsigned int	i;
		char			*tmp;

		tmp = NULL;
		i = check_line(*buf);
		*line = ft_strdup(*buf);
		tmp = ft_strdup(*buf + i);
		free(*buf);
		*buf = tmp;
		if (buf2)
				free(*buf2), *buf2 = NULL;
		return (1);
}

int					get_next_line(int const fd, char **line)
{
		int				f;
		char			*buf2;
		static char		*buf = NULL;

		buf2 = NULL;
		if (fd <= 0 || (!(line)) || BUFF_SIZE < 1)
				return (-1);
		if ((!(buf2 = (char*)malloc(sizeof(char) * BUFF_SIZE + 1))))
				return (-1);
		while (((f = read(fd, buf2, BUFF_SIZE)) > 0) && (!(ft_strchr(buf2, '\n'))))
				buf2[f] = '\0', join_buf(&buf2, &buf);
		if (buf2 && *buf2 && f > 0)
				buf2[f] = '\0', join_buf(&buf2, &buf);
		if (f < 0)
				return (-1);
		if (buf && buf[0] != '\0')
				return (return_line(&buf, &buf2, line));
		if (buf2)
				free(buf2), buf2 = NULL;
		free(buf), buf = NULL;
		*line = NULL;
		return (0);
}
