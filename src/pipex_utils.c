/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:00:04 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/26 17:06:54 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Function to create a complete path from a part of PATH
// And add the command to it
char	*parse_path(char *path, char *arg)
{
	char	*exe;
	char	*tmp;
	int		i;
	int		path_len;

	path_len = 0;
	while (path[path_len] && path[path_len] != ':')
		path_len++;
	tmp = malloc(sizeof(char) * (path_len + 2));
	if (!tmp)
		exit(1);
	i = 0;
	while (i < path_len)
	{
		tmp[i] = path[i];
		i++;
	}
	tmp[i++] = '/';
	tmp[i] = '\0';
	exe = ft_strjoin(tmp, arg);
	free(tmp);
	return (exe);
}

// Function to find the complete path of a command, by using the env PATH
char	*get_path(char **envp, char *arg)
{
	int		i;
	char	*path;
	char	*exe;

	i = 0;
	path = NULL;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5))
		i++;
	if (!envp[i])
		return (arg);
	path = envp[i] + 5;
	while (*path)
	{
		if (path == envp[i] + 5 || *path == ':')
		{
			exe = parse_path(path + !(path == envp[i] + 5), arg);
			if (access(exe, F_OK) == 0)
				return (exe);
			free(exe);
		}
		path++;
	}
	return (arg);
}

// A simple function to display an error message
void	error(char *name, char *err)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
}
