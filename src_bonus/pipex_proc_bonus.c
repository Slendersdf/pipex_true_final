/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_proc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:39:43 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/10/16 15:16:29 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Function to handle a child process and execute it
void	child_process(int fd_in, int fd_out, char *cmd, char **env)
{
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close(fd_in);
	close(fd_out);
	run(cmd, env);
}

// Function that handle the second child process
// Redirection of Stdin to the read end of the pipe
// Redirection of Stdout to outfile
// Close unutilized fd
// Execute the second (last) command
void	second_child(int outfile, int *fd_pipe, char *cmd, char **env)
{
	dup2(fd_pipe[0], 0);
	dup2(outfile, 1);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(outfile);
	run(cmd, env);
}

// Function to handle all the procs, including the parent one
void	parent_process(int infile, int outfile, char **av, char **env, int ac)
{
	int	fd_pipe[2];
	int	fd_in;
	int i;
	int pid;

	fd_in = infile;
	i = 2;
	while (i < ac - 2)
	{
		pipe(fd_pipe);
		pid = fork();
		if (pid == 0)
		{
			close(fd_pipe[0]);
			child_process(fd_in, fd_pipe[1], av[i], env);
		}
		else
		{
			close(fd_pipe[1]);
			close(fd_in);
			fd_in = fd_pipe[0];
			waitpid(pid, NULL, 0);
		}
		i++;
	}
	// Last command
	pid = fork();
	if (pid == 0)
		child_process(fd_in, outfile, av[i], env);
	else
	{
		close(fd_in);
		close(outfile);
		waitpid(pid, NULL, 0);
	}
}
