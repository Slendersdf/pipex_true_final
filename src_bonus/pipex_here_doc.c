/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:22:08 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/10/16 17:26:45 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Function to handle here_doc behavior
void	handle_here_doc(char *limiter, char **av, char **env, int outfile)
{
	int		fd_pipe[2];
	int		fd_pipe_cmd[2];
	int		id;
	char	*line;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	if (pipe(fd_pipe) == -1 || pipe(fd_pipe_cmd) == -1)
		error("pipe", strerror(errno));
	id = fork();
	if (id == 0)
	{
		close(fd_pipe[0]);
		while (1)
		{
			ft_putstr_fd("heredoc> ", 1);
			line = get_next_line(0);
			if (!line || (ft_strncmp(line, limiter, limiter_len) == 0 && line[limiter_len] == '\n'))
				break;
			write(fd_pipe[1], line, ft_strlen(line));
			free(line);
		}
		free(line);
		close(fd_pipe[1]);
		exit(0);
	}
	else
	{
		close(fd_pipe[1]);
		if (fork() == 0)
		{
			dup2(fd_pipe[0], 0);
			dup2(fd_pipe_cmd[1], 1);
			close(fd_pipe_cmd[0]);
			run(av[3], env);
		}
		if (fork() == 0)
		{
			close(fd_pipe_cmd[1]);
			dup2(fd_pipe_cmd[0], 0);
			dup2(outfile, 1);
			run(av[4], env);
		}
		close(fd_pipe[0]);
		close(fd_pipe_cmd[0]);
		close(fd_pipe_cmd[1]);
		wait(NULL);
		wait(NULL);
		waitpid(id, NULL, 0);
	}
	// HAVE TO CUT IT IN MULTIPLE FUNCTIONS
}
