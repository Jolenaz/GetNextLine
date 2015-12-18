/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:44:26 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/18 14:34:17 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	ft_cop(char **str1, char **line, char **str2)
{
	*(ft_strchr(*str1, '\n')) = '\0';
	if ((*line = ft_strjoin(*line, *str1)) == NULL)
		return (-1);
	free(*str2);
	if ((*str2 = ft_strdup(ft_strchr(*str1, '\0') + 1)) == NULL)
		return (-1);
	return (1);
}

static int	read_get_next_line(const int fd, char **line, char **rest)
{
	char		*buff;
	int			tete;
	char		**vid;

	buff = NULL;
	vid = (char**)malloc(sizeof(char*));
	*vid = NULL;
	if ((buff = ft_strnew(BUFF_SIZE + 1)) == NULL)
		return (-1);
	if (*rest == NULL)
		*rest = ft_strnew(BUFF_SIZE);
	else if (ft_strchr(*rest, '\n') != NULL)
		return (ft_cop(rest, line, rest));
	else if ((*line = ft_strjoin(*line, *rest)) == NULL)
		return (-1);
	while ((tete = read(fd, buff, BUFF_SIZE)) && tete != -1)
	{

		if (tete <= BUFF_SIZE)
			buff[tete] = 0;
		if (ft_strchr(buff, '\n') != NULL)
			return (ft_cop(&buff, line, rest));
		else
		{
			if ((*vid = ft_strjoin(*line, buff)) == NULL)
				return(-1);
			ft_strdel(line);
			*line = *vid;
		}
	}
	ft_strdel(&buff);
	return (tete);
}

int			get_next_line(const int fd, char **line)
{
	static t_doc	doc;
	t_doc			*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	if ((*line = ft_strnew(1)) == NULL)
		return (-1);
	tmp = &doc;
	if (tmp->rest == NULL)
	{
		doc.filed = fd;
		doc.next = NULL;
		doc.rest = NULL;
		return (read_get_next_line(fd, line, &(doc.rest)));
	}
	while (tmp->filed != fd && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->filed != fd)
	{
		if ((tmp->next = (t_doc*)malloc(sizeof(t_doc))) == NULL)
			return (-1);
		tmp->next->filed = fd;
		tmp->next->next = NULL;
		tmp->next->rest = NULL;
		return (read_get_next_line(fd, line, &tmp->next->rest));
	}
	return (read_get_next_line(fd, line, &tmp->rest));
}
