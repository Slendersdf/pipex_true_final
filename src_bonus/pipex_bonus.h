/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:35:46 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/10/15 15:36:39 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_BONUS_H
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

//pipex.c
void	exe(char **cmd, char **env);
void	run(char *arg, char **env);
//pipex_proc.c
void 	child_process(int infile, int outfile, char *cmd, char **env);
void	parent_process(int infile, int outfile, char **av, char **env, int ac);
//pipex_utils.c
char	*get_path(char **env, char *arg);
char	*parse_path(char *path, char *arg);
void	error(char *name, char *err);
#endif
