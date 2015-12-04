/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:44:26 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/04 14:26:17 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_initbuffer(char *ptb, int buff_size)
{
	int i;

	i = 0;
	while (i < buff_size)
	{
		ptb[i] = 0;
		i++;
	}
}

static int	ft_cop(char *str1, char **line, char *str2)
{
	*(ft_strchr(str1, '\n')) = '\0';
	*line = ft_strjoin(*line, str1);
	ft_strcpy(str2, str1 + ft_strlen(str1) + 1);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			tete;
	static char	*rest;

	ft_initbuffer(buff, BUFF_SIZE + 1);
	*line = ft_strnew(1);
	if (rest == NULL)
		rest = ft_strnew(BUFF_SIZE);
	if (ft_strchr(rest, '\n') != NULL)
		return (ft_cop(rest, line, rest));
	*line = ft_strjoin(*line, rest);
	while ((tete = read(fd, buff, BUFF_SIZE)) && tete != -1)
	{
		buff[BUFF_SIZE] = 0;
		if (ft_strchr(buff, '\n') != NULL)
			return (ft_cop(buff, line, rest));
		else
			*line = ft_strjoin(*line, buff);
	}
	return (tete);
}
