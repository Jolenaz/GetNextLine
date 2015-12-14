/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:44:26 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/14 16:54:49 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *ft_strjoinfree(char *str1, char *str2)
{
	char *res;
	char *tmp;
	char *tmp1;

	if ((res = (char*)malloc(ft_strlen(str1) + ft_strlen(str2) + 1)) == NULL)
		return (NULL);
	tmp = res;
	tmp1 = str1;
	while (*tmp1)
	{
		*tmp = *tmp1;
		tmp++;
		tmp1++;
	}
	while (*str2)
	{
		*tmp = *str2;
		tmp++;
		str2++;
	}
	*tmp = 0;
//	free(str1);
	return (res);
}


static int	ft_cop(char **str1, char **line, char **str2)
{
	*(ft_strchr(*str1, '\n')) = '\0';
	*line = ft_strjoinfree(*line, *str1);
	ft_strcpy(*str2, *str1 + ft_strlen(*str1) + 1);
	return (1);
}

static int	read_get_next_line(const int fd, char **line, char **rest)
{
	char		*buff;
	int			tete;

	buff = ft_strnew(BUFF_SIZE + 1);
	if (*rest == NULL)
		*rest = ft_strnew(BUFF_SIZE);
	else if (ft_strchr(*rest, '\n') != NULL)
		return (ft_cop(rest, line, rest));
	else
		*line = ft_strjoinfree(*line, *rest);
	while ((tete = read(fd, buff, BUFF_SIZE)) && tete != -1)
	{
		buff[tete] = 0;
		if (ft_strchr(buff, '\n') != NULL)
			return (ft_cop(&buff, line, rest));
		else
			*line = ft_strjoinfree(*line, buff);
	}
	return (tete);
}

int			get_next_line(const int fd, char **line)
{
	static t_doc	doc;
	t_doc			*tmp;

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
