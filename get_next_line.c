/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <jmakela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:37:09 by jmakela           #+#    #+#             */
/*   Updated: 2019/11/21 16:13:47 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Ft_str_op finds the first \n or \0 in the case where no new line is found.
** If \n was found, we create substr of arr[fd] starting from 0 and ending
** at index length. Line points to this new substr.
** Strdup remainder of arr[fd] into temp. Index + 1 is used so we skip the \n.
** Clear arr[fd] and assign duplicated string temp into arr[fd].
** This duplicated string is the remainder after \n.
** Check if arr[fd] has been emptied (no remainder left) and clear it if empty.
** If no \n was found (the case with single long line), make line point to
** strdup of the whole arr[fd]. Return 1 for successfully read line.
*/

static int	ft_str_op(int fd, char **line, char **arr)
{
	int		index;
	char	*temp;

	index = 0;
	while (arr[fd][index] != '\n' && arr[fd][index] != '\0')
		index = index + 1;
	if (arr[fd][index] == '\n')
	{
		*line = ft_strsub(arr[fd], 0, index);
		temp = ft_strdup(arr[fd] + index + 1);
		ft_strdel(&arr[fd]);
		arr[fd] = temp;
		if (arr[fd][0] == '\0')
			ft_strdel(&arr[fd]);
	}
	else
	{
		*line = ft_strdup(arr[fd]);
		ft_strdel(&arr[fd]);
	}
	return (1);
}

/*
** Get_next_line reads a line from a file descriptor.
** Returns -1 for error, 1 for line read or 0 for completed reading.
** Uses static two dimensional array to handle up to 10000 different fds.
** While there is stuff left to read, strjoin read chars (buf) and arr[fd],
** into temp string, clears arr[fd] and assigns joined string to arr[fd].
** Check for \n in the string that was read, if found, break loop.
** Basically we keep appending BUFF_SIZE amount of read chars into arr[fd]
** until we run out of stuff to read or we encounter \n in the read chars.
*/

int			get_next_line(const int fd, char **line)
{
	static char	*arr[10000];
	char		buf[BUFF_SIZE + 1];
	char		*temp;
	int			i;

	if (fd < 0 || fd > 10000 || !line)
		return (-1);
	while ((i = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[i] = '\0';
		if (!arr[fd])
			arr[fd] = ft_strnew(1);
		temp = ft_strjoin(arr[fd], buf);
		ft_strdel(&arr[fd]);
		arr[fd] = temp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (i < 0)
		return (-1);
	if (!i && !arr[fd])
		return (0);
	return (ft_str_op(fd, line, arr));
}
