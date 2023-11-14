/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:13:07 by mshereme          #+#    #+#             */
/*   Updated: 2023/11/14 10:29:57 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(char *s, int c)
{
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			return (1);
		s++;
	}
	if (c == 0)
		return (1);
	return (0);
}

char	*ft_newline(char *line)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = malloc((ft_strlen(line) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

char	*ft_inscribe(char *line, char *str, size_t j)
{
	while (line[j] != '\0')
	{
		if (line[j] == '\n')
		{
			str[j++] = '\n';
			str[j] = '\0';
			return (str);
		}
		str[j] = line[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_get_line(char *line)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!*line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str = ft_inscribe(line, str, j);
	return (str);
}
