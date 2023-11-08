/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:25:25 by mshereme          #+#    #+#             */
/*   Updated: 2023/11/08 18:53:47 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

// Can add the content of the buff to the end of the list
void	ft_append(t_list **list, char *buff, size_t c_read)
{
	t_list	*new_node;
	t_list	*last_node;
	size_t	i;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->str_buf = malloc((c_read + 1) * sizeof(char));
	if (!new_node->str_buf)
		return ;
	i = 0;
	while (buff[i] && i < c_read)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	last_node = ft_lstlast(lst);
	last_node->next = new_node;
}
// Read from fd and add to the lst
void	ft_creatlist(t_list **lst, int fd)
{
	size_t	c_read;
	char	*buff;

	while (ft_newline(*lst) == 0 && c_read != 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return ;
		if ((*lst == NULL && c_read == 0) || c_read < 0)
		{
			free(buff);
			return ;
		}
		c_read = read(fd, buff, BUFFER_SIZE);
		buff[c_read] = '\0';
		ft_append(lst, buff, c_read);
		free(buff);
	}
}
/* Extract all char from the lst and put them in the line */
void	ft_extract_line(t_list *lst, char **line)
{
	int	i;
	int	j;

	if (!lst)
		return ;
	ft_generate_line(line, lst);
	if (!(*line))
		return ;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i])
			{
				*line[j++] = lst->content[i];
				break ;
			}
			*line[j++] = lst->content[i++];
		}
		lst = lst->next;
	}
	*line[j] = '\0';
}

void	ft_clean_lst(t_list **lst)
{
	t_list	*last;
	t_list	*clean_node;
	int	i;
	int	j;

	if (!lst)
		return ;
	clean_node = malloc(sizeof(t_list));
	if (!clean_node)
		return ;
	clean_node->next = NULL;
	last = ft_lstlast(lst);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloci(((ft_strlen(last->content) - i + 1) * sizeof(char)));
	if (!clean_node->content)
		return ;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_list(lst);
	*lst = clean_node;
}


char	*get_next_line(int fd)
{
	static t_list	*lst;
	char		*line;

	lst = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);

	// 1. On veut read from fd and add to linked list
	ft_creatlist(&lst, fd);
	if (!lst)
		return (NULL);
	// 2. Extraire from stash to line
	ft_extract_line(lst, &line)
	// 3. Clean up notre lst
	ft_lst_clean(lst);
	if (*line = '\0')
	{
		ft_free_lst(lst);
		lst = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(int ac, char **av)
{
	int	fd;
	char	*str;
	
	fd = open(av[i],O_RDONLY);
	if (fd < 0)
		return (write(1, "NON", 3));
	
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break;
		printf("%s\n", str);
		free(str);
	}
	close(fd);
	return (0);
}
