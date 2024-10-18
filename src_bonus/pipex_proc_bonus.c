/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_proc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:39:43 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/10/18 16:14:05 by fpaulas-         ###   ########.fr       */
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

void	process_commands(int fd_in, char **av, char **env, int ac)
{
	int	fd_pipe[2];
	int	pid;
	int	i;

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
	last_process(fd_in, av, env, ac);
}

void	last_process(int fd_in, char **av, char **env, int ac)
{
	int pid;
	int outfile;

	outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (outfile == -1)
	{
		error(av[ac - 1], strerror(errno));
		exit(1);
	}
	pid = fork();
	if (pid == 0)
		child_process(fd_in, outfile, av[ac - 2], env);
	else
	{
		close(fd_in);
		close(outfile);
		waitpid(pid, NULL, 0);
	}
}

// Function to handle all the procs, including the parent one
// Loop to execute each command except the last one (so we stop at ac - 2)
// Create pipe at each
// Fork each child
// If child proc is created
// it closes pipe read end
// redirect STDIN and STDOUT and execute cmd (child_process())
// If it's parent process then it closes write end of the pipe
// close actual entry (fd_in)
// and tranfer a new one to the write end of the pipe
// to use it as a new entry for the next cmd
// And we repeat the process for each child process
// After the loop, the final process (the "last" one) is created
// to execute the last cmd then we wait for it to finish
void	parent_process(int infile, char **av, char **env, int ac)
{
	process_commands(infile, av, env, ac);
}
