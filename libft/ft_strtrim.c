/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:16:33 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/26 17:50:39 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_comp(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static size_t	ft_index(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_comp(set, s1[start]) == 0)
	{
		start++;
	}
	while (ft_comp(set, s1[end]) == 0)
	{
		end--;
	}
	return (end + 1 - start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	char	*s_trim;
	size_t	i;

	if (s1[0] == '\0')
		return (ft_strdup(""));
	start = 0;
	i = 0;
	while (ft_comp(set, s1[start]) == 0)
		start++;
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	s_trim = ft_calloc(ft_index(s1, set) + 1, sizeof(char));
	if (s_trim == NULL)
		return (NULL);
	while (i < ft_index(s1, set))
	{
		s_trim[i] = s1[start];
		i++;
		start++;
	}
	return (s_trim);
}
