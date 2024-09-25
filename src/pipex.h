/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:59:05 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/09/16 12:15:26 by fpaulas-         ###   ########.fr       */
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
char 	*parse_path(char *path, char *arg);
void	error(char *name, char *err);

void	exe(char **cmd, char **envp);
void	run(char *arg, char **envp);
void	mk_pipe(int fd1, int fd2, char **argv, char **envp);
#endif
