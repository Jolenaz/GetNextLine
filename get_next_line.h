/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:59:48 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/14 09:22:58 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# define BUFF_SIZE 100

int					get_next_line(const int fd, char **line);

typedef struct		s_doc
{
	int				filed;
	char			*rest;
	struct s_doc	*next;
}					t_doc;

#endif
