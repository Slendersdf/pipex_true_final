/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:58:41 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/26 14:24:12 by fpaulas-         ###   ########.fr       */
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

// Function to handle a child process
// Redirection of Stdin (0) to infile/read end of the pipe
// Redirection of Stdout (1) to outfile/write end of the pipe
// Close write/read end of the pipe (child side)
// Execute the command
// Close infile and outfile since they are no useful anymore (child side)
void	first_child(int fd_in, int fd_pipe[2], char *cmd, char **envp)
{
	// Rediriger stdin vers infile
	dup2(fd_in, 0);

	// Rediriger stdout vers l'extrémité d'écriture du pipe
	dup2(fd_pipe[1], 1);

	// Fermer les descripteurs inutilisés
	close(fd_pipe[0]);  // Fermer l'extrémité de lecture du pipe
	close(fd_pipe[1]);
	close(fd_in);

	// Exécuter la commande
	run(cmd, envp);

	// En cas d'échec de la commande
	exit(1);
}

void	second_child(int fd_out, int fd_pipe[2], char *cmd, char **envp)
{
	// Rediriger stdin vers l'extrémité de lecture du pipe
	dup2(fd_pipe[0], 0);

	// Rediriger stdout vers outfile
	dup2(fd_out, 1);

	// Fermer les descripteurs inutilisés
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(fd_out);

	// Exécuter la commande
	run(cmd, envp);

	// En cas d'échec de la commande
	exit(1);
}


// Function to create a pipe and handle both of childs process
void	parent_process(int infile, int outfile, char **argv, char **envp)
{
	int	fd_pipe[2];
	int	id1;
	int	id2;

	id1 = 0;
	id2 = 0;
	pipe(fd_pipe);
	id1 = fork();
	if (id1 == 0)
		first_child(infile, fd_pipe, argv[2], envp);
	id2 = fork();
	if (id2 == 0)
		second_child(outfile, fd_pipe, argv[3], envp);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(infile);
	close(outfile);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
}

// Main function, pretty obvious XD
int	main(int argc, char **argv, char *envp[])
{
	int	infile;
	int	outfile;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
		{
			error(argv[1], strerror(errno));
			return (1);
		}
		outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (outfile == -1)
		{
			error(argv[4], strerror(errno));
			return (1);
		}
		parent_process(infile, outfile, argv, envp);
		return (0);
	}
	ft_putstr_fd("Incorrect format! Try this format : ./pipex file1 cmd1 cmd2 file2\n", 2);
	return (1);
}
