/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:21:40 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/05/29 16:05:54 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*temp;

	i = 0;
	temp = 0;
	while (s[i])
	{
		if (s[i] == ((unsigned char)c))
			temp = ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		temp = ((char *)&s[i]);
	return (temp);
}
