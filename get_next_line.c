/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:44:26 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/03 16:05:22 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void ft_initbuffer(char **ptb, int buf_size)
{
	int i;

	i = 0;
	while (i < buf_size)
	{
		*ptb[i] = 0;
		i++;
	}
}

int	get_next_line(const int fd, char **line)
{

	return (ret);
}
