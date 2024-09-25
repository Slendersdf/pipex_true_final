/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:30:36 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/06/06 23:19:21 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	cpt;
	int	i;
	int	trigger;

	i = 0;
	cpt = 0;
	trigger = 0;
	while (s[i])
	{
		if (s[i] != c && trigger == 0)
		{
			trigger = 1;
			cpt++;
		}
		else if (s[i] == c)
			trigger = 0;
		i++;
	}
	return (cpt);
}

static char	*add_words(char const *s, int start, int end)
{
	char	*act_word;
	int		i;

	i = 0;
	act_word = ft_calloc(end + 1 - start, sizeof(char));
	if (act_word == NULL)
		return (NULL);
	while (start < end)
	{
		act_word[i] = s[start];
		i++;
		start++;
	}
	return (act_word);
}

static void	*ft_free_array(char **s, int cpt)
{
	int	i;

	i = 0;
	while (i < cpt)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**s_split;
	size_t	i;
	int		j;
	int		trigger;

	i = 0;
	j = 0;
	trigger = -1;
	s_split = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (s_split == NULL)
		return (NULL);
	while (i < ft_strlen(s) + 1)
	{
		if (s[i] != c && trigger < 0)
			trigger = i;
		else if ((s[i] == c || i == ft_strlen(s)) && trigger >= 0)
		{
			s_split[j] = add_words(s, trigger, i);
			if (s_split[j++] == NULL)
				return (ft_free_array(s_split, j));
			trigger = -1;
		}
		i++;
	}
	return (s_split);
}
