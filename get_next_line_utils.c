/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:13:17 by mshereme          #+#    #+#             */
/*   Updated: 2023/11/08 18:52:23 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_newline(t_list *lst)
{
	int	i;
	t_list	*current;

	if (!lst)
		return (0);
	current = ft_lstlast(lst);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i])
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_generate_line(char **line, t_list *lst)
{
	int	i;
	int	len;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				len++;
				break;
			}
			len++;
			i++;
		}
		lst = lst->next;
	}
	*line = malloc((len + 1) * sizeof(char));

}

void	ft_free_lst(t_list *lst)
{
	t_list	*current;
	t_list	*next;

	current = lst;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
