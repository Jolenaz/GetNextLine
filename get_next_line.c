/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:44:26 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/14 10:28:40 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	ft_cop(char **str1, char **line, char **str2)
{
	char *vid;

	vid = *line;
	*(ft_strchr(*str1, '\n')) = '\0';
	*line = ft_strjoin(*line, *str1);
	free(vid);
	ft_strcpy(*str2, *str1 + ft_strlen(*str1) + 1);
	return (1);
}

int			read_get_next_line(const int fd, char **line, char **rest)
{
	char		*buff;
	int			tete;

	buff = ft_strnew(BUFF_SIZE + 1);
	if (*rest == NULL)
		*rest = ft_strnew(BUFF_SIZE);
	if (ft_strchr(*rest, '\n') != NULL)
		return (ft_cop(rest, line, rest));
	*line = ft_strjoin(*line, *rest);
	while ((tete = read(fd, buff, BUFF_SIZE)) && tete != -1)
	{
		buff[tete] = 0;
		if (ft_strchr(buff, '\n') != NULL)
			return (ft_cop(&buff, line, rest));
		else
			*line = ft_strjoin(*line, buff);
	}
	free(buff);
	return (tete);
}

int get_next_line(const int fd, char **line)
{
	static t_doc doc;
	t_doc *tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = ft_strnew(1);
	tmp = &doc;
	if (tmp->filed == 0)
	{
		doc.filed = fd;
		doc.next = NULL;
		return (read_get_next_line(fd, line, &(doc.rest)));
	}
	while (tmp->filed != fd && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->filed != fd)
	{
		tmp->next = (t_doc*)malloc(sizeof(t_doc));
		tmp->next->filed = fd;
		tmp->next->next = NULL;
		return (read_get_next_line(fd, line, &tmp->next->rest));
	}
	return (read_get_next_line(fd, line, &tmp->rest));
}
