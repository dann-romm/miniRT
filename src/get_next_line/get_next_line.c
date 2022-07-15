/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:17:16 by doalbaco          #+#    #+#             */
/*   Updated: 2022/07/15 11:59:53 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*data[1];
	char		*str;

	if (fd < 0 || fd > (OPEN_MAX - 1))
		return (0);
	if (!data[0])
	{
		data[0] = (char *) malloc(sizeof(char) * 1);
		if (!data[0])
			return (0);
		data[0][0] = 0;
	}
	read_file(data, fd);
	if (!data[0])
		return (0);
	str = cut_str(data);
	return (str);
}

void	read_file(char *data[1], int fd)
{
	char	*buffer;
	int		size;

	buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
	{
		free(data[0]);
		data[0] = 0;
		return ;
	}
	while (find(data[0], '\n') == -1)
	{
		size = read(fd, buffer, 1);
		if (size < 1)
		{
			if (size == -1 || data[0][0] == 0)
			{
				free(data[0]);
				data[0] = 0;
			}
			break ;
		}
		data[0] = concatenate(data[0], buffer, size);
	}
	free(buffer);
}

char	*cut_str(char *data[1])
{
	char	*str;
	int		i;
	int		j;

	if (!data[0])
		return (0);
	i = 0;
	while (data[0][i] && data[0][i] != '\n')
		i++;
	str = (char *) malloc(sizeof(char) * (i + (data[0][i] == '\n') + 1));
	if (!str)
		return (0);
	i = 0;
	while (data[0][i] && data[0][i] != '\n')
	{
		str[i] = data[0][i];
		i++;
	}
	str[i] = '\n';
	str[i + (data[0][i] == '\n')] = 0;
	j = i;
	while (data[0][j])
		j++;
	data[0] = tail(data[0], j - i - 1);
	return (str);
}
