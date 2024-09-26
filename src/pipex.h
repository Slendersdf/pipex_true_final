/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:59:05 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/26 14:17:27 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>

char	*get_path(char **envp, char *arg);
char	*parse_path(char *path, char *arg);
void	error(char *name, char *err);

void	exe(char **cmd, char **envp);
void	run(char *arg, char **envp);
void	first_child(int fd_in, int fd_pipe[2], char *cmd, char **envp);
void	second_child(int fd_out, int fd_pipe[2], char *cmd, char **envp);
void	parent_process(int infile, int outfile, char **argv, char **envp);
#endif
