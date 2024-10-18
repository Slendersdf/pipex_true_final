/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:22:08 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/10/18 16:01:23 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Function to handle here_doc behavior
// take a limiter (limit), program args (av), env variable (env)
// and output file (outfile)
void	handle_here_doc(char *limiter, char **av, char **env, int outfile)
{
	int		fd_pipe[2]; //Pipe to communicate data between parent and child (here_doc)
	int		fd_pipe_cmd[2]; // Pipe to transmit data of cmd after here_doc
	int		id; // Fork id
	char	*line; // Stock each line inputed by user
	int		limiter_len; // Limiter length

	// Limiter len is calculated, then both pipes are created
	// one for here_doc and the other for cmds
	limiter_len = ft_strlen(limiter);
	if (pipe(fd_pipe) == -1 || pipe(fd_pipe_cmd) == -1)
		error("pipe", strerror(errno));
	// CHILD //
	// A child proc is created to capture input (in here_doc)
	// It displays a prompt here_doc to let the user write code
	// If a line is the Limiter, then loops end
	// The lines inputed are written in the pipe
	// When all's done, the pipe is closed and child proc ends
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
	// PARENT //
	// The parent closes write end of the here_doc pipe
	// then, it creates a child proc to execute av[3] (cmd after here_doc part)
	// by redirecting STDIN (0) to the pipe and STDOUT (1) to the write end of the second pipe (fd_pipe_cmd)
	// An another child is created to execute av[4] (last cmd), with the previous pipe entry
	// and the output to the outfile
	// After both execution, pipes are closed and parent waits for childs
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
