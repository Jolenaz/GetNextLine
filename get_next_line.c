/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:44:26 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/08 12:13:30 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_cop(char *str1, char **line, char *str2)
{
	char *tmp;

	tmp = *line;
	*(ft_strchr(str1, '\n')) = '\0';
	*line = ft_strjoin(*line, str1);
	ft_strcpy(str2, str1 + ft_strlen(str1) + 1);
	free(tmp);
	return (1);
}

int			ft_read(char **line, t_doc *lst)
{
	char		*buff;
	int			tete;
	char		*vid;

	buff = ft_strnew(BUFF_SIZE + 1);
	*line = ft_strnew(1);
	if (ft_strchr(lst->rest, '\n') != NULL)
		return (ft_cop(lst->rest, line, lst->rest));
	vid = *line;
	*line = ft_strjoin(*line, lst->rest);
	free(vid);
	while ((tete = read(lst->filed, buff, BUFF_SIZE)) && tete != -1)
	{
		buff[tete] = 0;
		if (ft_strchr(buff, '\n') != NULL)
			return (ft_cop(buff, line, lst->rest));
		else
		{
			vid = *line;
			*line = ft_strjoin(*line, buff);
			free(vid);
		}
	}
	free(buff);
	return (tete);
}

t_doc		*ft_docnew(const int fd)
{
	t_doc *tmp;

	if ((tmp = (t_doc*)malloc(sizeof(t_doc))) == NULL)
		return (NULL);
	tmp->filed = fd;
	tmp->rest = ft_strnew(BUFF_SIZE);
	if (tmp->rest == NULL)
		return (NULL);
	tmp->next = NULL;
	return (tmp);
}

int			get_next_line(const int fd, char **line)
{
	static t_doc	*lst;
	t_doc			*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	if (lst == NULL)
	{
		if ((lst = ft_docnew(fd)) == NULL)
			return (-1);
	}
	tmp = lst;
	while (tmp->filed != fd)
	{
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
	}
	if (tmp == NULL)
	{
		if ((tmp = ft_docnew(fd)) == NULL)
			return (-1);
	}
	return (ft_read(line, tmp));
}
