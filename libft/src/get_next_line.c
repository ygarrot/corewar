/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 08:45:37 by gmonnier          #+#    #+#             */
/*   Updated: 2018/03/11 17:25:42 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_fill_line(char **line, char **sta_buff)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while ((*sta_buff)[++i] != '\n' && (*sta_buff)[i])
		;
	*line = ft_strsub(*sta_buff, 0, i);
	if (ft_strlen(*sta_buff) > 0)
		tmp = ft_strsub(*sta_buff, i + 1, ft_strlen(*sta_buff) - i);
	free(*sta_buff);
	*sta_buff = tmp;
}

int			loop(const int fd, char *sta_buff[MAX_FD], int ret[MAX_FD])
{
	char *tmp;
	char buff[BUFF_SIZE + 1];

	while (!ft_strchr(sta_buff[fd], '\n'))
	{
		if ((ret[fd] = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		if (!ret[fd])
			break ;
		buff[ret[fd]] = '\0';
		tmp = ft_strjoin(sta_buff[fd], buff);
		free(sta_buff[fd]);
		sta_buff[fd] = tmp;
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*sta_buff[MAX_FD];
	static int	ret[MAX_FD];

	if (fd < 0 || !line || fd > 4864 || (read(fd, sta_buff[0], 0)) == -1)
		return (-1);
	if (!sta_buff[fd])
		mallcheck(sta_buff[fd] = ft_memalloc(1));
	if (loop(fd, sta_buff, ret) == -1)
		return (-1);
	if (ft_strcmp(sta_buff[fd], "") == 0)
		return (0);
	ft_fill_line(line, &sta_buff[fd]);
	return (1);
}
