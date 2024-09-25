/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:58:41 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/25 22:05:00 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Function that executes a command
// IF no "/" (probably a simple command), search the path with get_path
// Then execute it. In the case of failure, send a specific error message
// ELSE, in the case of "/" (so absolute or relative path probably)
// check if the file is executable, if it is then execute the command
// else, send a system error message
void	exe(char **cmd, char **envp)
{
	char	*path;

	if (!ft_strchr(cmd[0], '/'))
	{
		path = get_path(envp, cmd[0]);
		execve(path, cmd, envp);
		error(cmd[0], "command not found");
	}
	else
	{
		path = cmd[0];
		if (access(path, X_OK) != 0)
			error(path, strerror(errno));
		else
			execve(path, cmd, envp);
	}
}

// Function that execute the command by dividing it in multiple args, if necessary
// If arg is not empty, then it shall be divided in multiple part (ft_split | spaces)
// Then we execute the command (exe function) and free cmd if it fails
// Else, in the case of empty arg (""), we send a specific error message
void	run(char *arg, char **envp)
{
	char	**cmd;
	int		i;

	i = 0;
	if (*arg)
	{
		cmd = ft_split(arg, ' ');
		exe(cmd, envp);
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
	}
	else
	{
		error("", "command not found");
	}
	exit(127);
}

// Function that create a pipe between two process to execute "chained" commands
// First, we create a pipe and fork if "infile" (fd1) exists
// Child process //
// Redirection of STDIN (0) to the "infile"
// Then redirection of STDOUT (1) to the write end of the pipe
// Finally, execution of the "first" command
// Parent process //
// Redirection of STDOUT (1) to the "outfile"
// Then redirection of STDIN (0) to the read end of the pipe
// Wait for the end of the child process
// Finally, execution of the "second" command
void	mk_pipe(int fd1, int fd2, char **argv, char **envp)
{
	int		fd[2];
	int		id;

	id = 1;
	pipe(fd);
	if (fd1 != -1)
		id = fork();
	if (id == 0)
	{
		dup2(fd1, 0);
		close(fd[0]);
		dup2(fd[1], 1);
		run(argv[2], envp);
		close(fd1);
	}
	else
	{
		dup2(fd2, 1);
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
		run(argv[3], envp);
		close(fd2);
	}
}

// Main function, pretty obvious XD
int	main(int argc, char **argv, char *envp[])
{
	int	file1;
	int	file2;

	if (argc == 5)
	{
		file1 = open(argv[1], O_RDONLY);
		if (file1 == -1)
			error(argv[1], strerror(errno));
		file2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (file2 == -1)
		{
			error(argv[4], strerror(errno));
			return (1);
		}
		mk_pipe(file1, file2, argv, envp);
	}
	ft_putstr_fd("Incorrect format! Try this format : ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (1);
}
