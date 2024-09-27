/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:58:41 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/27 11:23:02 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Function that executes a command
// IF no "/" (probably a simple command), search the path with get_path
// Then execute it. In the case of failure, send a specific error message
// ELSE, in the case of "/" (so absolute or relative path probably)
// check if the file is executable, if it is then execute the command
// else, send a system error message
void	exe(char **cmd, char **env)
{
	char	*path;

	if (!ft_strchr(cmd[0], '/'))
	{
		path = get_path(env, cmd[0]);
		execve(path, cmd, env);
		error(cmd[0], "command not found");
	}
	else
	{
		path = cmd[0];
		if (access(path, X_OK) != 0)
			error(path, strerror(errno));
		else
			execve(path, cmd, env);
	}
}

// Function that execute the command by dividing it in multiple args
// If arg is not empty or not composed of whitespaces,
// then it shall be divided in multiple part
// Then we execute the command (exe function) and free cmd if it fails
// Else, in the case of empty arg (""), we send a specific error message
void	run(char *arg, char **env)
{
	char	**cmd;
	int		i;
	char	*trimmed;

	i = 0;
	trimmed = ft_strtrim(arg, " \t\n\f\r\v");
	if (*arg && trimmed[0] != '\0')
	{
		cmd = ft_split(arg, ' ');
		exe(cmd, env);
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		free(trimmed);
	}
	else
	{
		error("", "command not found");
		free(trimmed);
	}
	exit(127);
}

// Main function, pretty obvious XD
int	main(int ac, char **av, char *env[])
{
	int	infile;
	int	outfile;

	if (ac == 5)
	{
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
			error(av[1], strerror(errno));
		outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (outfile == -1)
		{
			error(av[4], strerror(errno));
			return (1);
		}
		parent_process(infile, outfile, av, env);
		return (0);
	}
	ft_putstr_fd("Incorrect format! ", 2);
	ft_putstr_fd("Try this one: ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (1);
}
