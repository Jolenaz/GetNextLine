/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:44:26 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/03 18:05:48 by jbelless         ###   ########.fr       */
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

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			tete;
	static char	*rest;

	ft_initbuffer(buff, BUFF_SIZE + 1);
	if (rest == NULL)
		rest = ft_strnew(1);
	if (ft_strchr(rest, '\n') != NULL)
	{
		*(ft_strchr(rest, '\n') + 1) = '\0';
		*line = ft_strjoin(*line, rest);
		ft_strcpy(rest, rest + ft_strlen(rest) + 1);
		return (1);
	}

	while ((tete = read(fd, buff, BUFF_SIZE)) && tete != -1)
	{
		buff[BUFF_SIZE] = 0;
		ft_putstr("\n___0___\n");
		ft_putstr(buff);
		ft_putstr("\n___0___\n");
		if (ft_strchr(buff, '\n') != NULL)
		{

			*(ft_strchr(buff, '\n')) = '\0';
			ft_putstr("\nlalalalalalal_______");
			ft_putstr(buff);
			ft_putstr("______lalalalalala\n");
			*line = ft_strjoin(*line, buff);
			ft_strcpy(rest, buff + ft_strlen(buff) + 1);
			return (1);
		}
		else
			*line = ft_strjoin(*line, buff);
	}
	return (tete);
}
