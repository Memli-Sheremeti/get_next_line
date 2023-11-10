/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:40:29 by mshereme          #+#    #+#             */
/*   Updated: 2023/11/10 15:57:04 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_creat_line(char *line, int fd)
{
	ssize_t	nb_bytes_read;
	char	*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return NULL;
	nb_bytes_read = 1;
	while (!ft_strchr(line, '\n') && nb_bytes_read != 0)
	{
		nb_bytes_read = read(fd, buf, BUFFER_SIZE);
		if (nb_bytes_read == -1)
		{
			free(buf);
			return NULL;
		}
		buf[nb_bytes_read] = '\0';
		line = ft_strjoin(line, buf);
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static	char	*line = NULL;
	char	*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	/*1. Qui doit stocker le nombre de bytes lu a chaque fois jusqua '\n'*/
	line = ft_creat_line(line, fd);
	if (!line)
		return (NULL);
	next_line = ft_get_line(line);
	line = ft_newline(line);
	return (next_line);	
}

/*int	main(int ac, char **av)
{
	int	fd;
	char	*line;

	(void) ac;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	free(line);
	close(fd);
	return (1);
}
*/
