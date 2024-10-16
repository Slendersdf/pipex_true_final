/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:48:22 by fpaulas-          #+#    #+#             */
/*   Updated: 2024/06/17 23:17:01 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Function that reads from the file descriptor fd
// And fills a buffer with characters until it finds a newline character (\n)
// Or reaches the end of the file

static char	*fill_line_buffer(int fd, char *remaining, char *buffer)
{
	ssize_t	bytes_readed;
	char	*temp;

	bytes_readed = 1;
	while (bytes_readed > 0)
	{
		bytes_readed = read(fd, buffer, BUFFER_SIZE);
		if (bytes_readed == -1)
		{
			free(remaining);
			return (NULL);
		}
		else if (bytes_readed == 0)
			break ;
		buffer[bytes_readed] = '\0';
		if (remaining == NULL)
			remaining = ft_strdup("");
		temp = remaining;
		remaining = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (remaining);
}

// Function that takes a string line_buffer
// And extracts the remaining characters after the newline character (\n).

static char	*set_line(char *line_buffer)
{
	ssize_t	i;
	char	*remaining;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	remaining = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (remaining == NULL || remaining[0] == '\0')
	{
		free(remaining);
		remaining = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (remaining);
}

// Function that reads a line from a file descriptor fd
// And returns it (one by one if multiple line for each call)

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*line;
	char		*buffer;

	if (BUFFER_SIZE < 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(remaining);
		free(buffer);
		remaining = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = fill_line_buffer(fd, remaining, buffer);
	free(buffer);
	buffer = NULL;
	if (line == NULL)
		return (NULL);
	remaining = set_line(line);
	return (line);
}
