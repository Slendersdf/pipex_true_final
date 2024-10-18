/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:35:46 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/10/18 16:16:46 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

//pipex_bonus.c
void	exe(char **cmd, char **env);
void	run(char *arg, char **env);
//pipex_here_doc.c
void	handle_here_doc(char *limiter, char **av, char **env, int outfile);
//pipex_proc_bonus.c
void	second_child(int outfile, int *fd_pipe, char *cmd, char **env);
void	child_process(int infile, int outfile, char *cmd, char **env);
void	process_commands(int fd_in, char **av, char **env, int ac);
void	last_process(int fd_in, char **av, char **env, int ac);
void	parent_process(int infile, char **av, char **env, int ac);
//pipex_utils_bonus.c
char	*get_path(char **env, char *arg);
char	*parse_path(char *path, char *arg);
void	error(char *name, char *err);
#endif
