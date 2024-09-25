/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:11:19 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/05/28 17:25:38 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = malloc(nmemb * size);
	if (temp == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		temp[i] = '\0';
		i++;
	}
	return (temp);
}
