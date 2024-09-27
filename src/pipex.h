/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:59:05 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/27 11:20:38 by fpaulas-         ###   ########.fr       */
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

//pipex.c
void	exe(char **cmd, char **env);
void	run(char *arg, char **env);
//pipex_proc.c
void	first_child(int fd_in, int *fd_pipe, char *cmd, char **env);
void	second_child(int fd_out, int *fd_pipe, char *cmd, char **env);
void	parent_process(int infile, int outfile, char **av, char **env);
//pipex_utils.c
char	*get_path(char **env, char *arg);
char	*parse_path(char *path, char *arg);
void	error(char *name, char *err);
#endif
