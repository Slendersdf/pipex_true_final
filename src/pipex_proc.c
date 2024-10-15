/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:51:51 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/27 15:08:13 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Function that handle the first child process
// Redirection of Stdin (0) to infile
// Redirection of Stdout (1) to the write end of the pipe
// Close unutilized fd
// Execute the first command
void	first_child(int infile, int *fd_pipe, char *cmd, char **env)
{
	if (infile == -1)
		exit(1);
	dup2(infile, 0);
	dup2(fd_pipe[1], 1);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(infile);
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

// Function to create a pipe and handle both of childs process
void	parent_process(int infile, int outfile, char **av, char **env)
{
	int	fd_pipe[2];
	int	id1;
	int	id2;

	id1 = 0;
	id2 = 0;
	pipe(fd_pipe);
	id1 = fork();
	if (id1 == 0)
		first_child(infile, fd_pipe, av[2], env);
	id2 = fork();
	if (id2 == 0)
		second_child(outfile, fd_pipe, av[3], env);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(infile);
	close(outfile);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
}
