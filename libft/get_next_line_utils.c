/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:59:34 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/12 09:59:36 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin_gnl(char *data, char *buffer)
{
	char	*join;
	int		i;
	int		j;

	join = malloc(sizeof(char) * ((ft_strlen_gnl(data)
					+ ft_strlen_gnl(buffer)) + 1));
	if (join == NULL)
		return (NULL);
	i = 0;
	while (data != NULL && data[i] != '\0')
	{
		join[i] = data[i];
		i++;
	}
	if (data != NULL)
		free(data);
	j = 0;
	while (buffer != NULL && buffer[j] != '\0')
	{
		join[i] = buffer[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

int	ft_strcontains(char *str, char c)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
