/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:16:52 by doalbaco          #+#    #+#             */
/*   Updated: 2022/07/15 11:59:48 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concatenate(char *dst, const char *buffer, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (dst[i])
		i++;
	tmp = (char *) malloc(sizeof(char) * (i + size + 1));
	if (!tmp)
	{
		free(dst);
		return (0);
	}
	j = -1;
	while (dst[++j])
		tmp[j] = dst[j];
	j = -1;
	while (++j < size)
		tmp[i + j] = buffer[j];
	tmp[j + i] = 0;
	free(dst);
	return (tmp);
}

char	*tail(char *dst, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (dst[i])
		i++;
	if (size > i)
		return (dst);
	if (size <= 0)
	{
		free(dst);
		return (0);
	}
	tmp = (char *) malloc(sizeof(char) * (size + 1));
	if (tmp)
	{
		j = -1;
		while (++j < size)
			tmp[j] = dst[i - size + j];
		tmp[j] = 0;
	}
	free(dst);
	return (tmp);
}

int	find(const char *str, char c)
{
	int	i;

	if (!str)
		return (-2);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
