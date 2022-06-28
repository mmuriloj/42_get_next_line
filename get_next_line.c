/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumontei <mumontei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:39:37 by mumontei          #+#    #+#             */
/*   Updated: 2022/06/28 21:00:36 by mumontei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_line(char *static_str)
{
	int		i;
	char	*str;

	if (!static_str)
		return (NULL);
	i = 0;
	while (static_str[i] && static_str[i] != '\n')
		i++;
	if (static_str[i] == '\n')
		str = (char *)malloc((i + 2) * sizeof(char));
	else
		str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (static_str[i] && static_str[i] != '\n')
	{
		str[i] = static_str[i];
		i++;
	}
	if (static_str[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_endside(char *static_str)
{
	int		i;
	int		j;
	char	*end;
	
	i = 0;
	j = 0;
	if (!static_str)
	{
		//free(static_str);
		static_str = NULL;
		return (NULL);
	}
	while (static_str[i] && static_str[i] != '\n')
		i++;
	end = (char *)malloc(sizeof(char) * (ft_strlen(static_str) - i + 1));
	if (!end)
		return (NULL);
	if (static_str[i] == '\n')
		i++;
	while (static_str[i])
		end[j++] = static_str[i++];
	end[j] = '\0';
	free(static_str);
	return (end);
}

char	*save_buffer(int fd, char *static_str)
{
	char	*buffer;
	int		n_bytes;
	char	*temp;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	n_bytes = 1;
	while (n_bytes > 0 && ft_strchr(static_str, '\n') == NULL)
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		
		if (n_bytes <= 0)
			break ;
		if (!static_str)
		{
			static_str = (char *)malloc(1 * sizeof(char));
			static_str[0] = '\0';
		}
		buffer[n_bytes] = '\0';
		temp = static_str;
		static_str = ft_strjoin(temp, buffer);
		free(temp);
		
	}
	free(buffer);
	return (static_str);
}

char	*get_next_line(int fd)
{
	static char	*static_str;
	char		*line;

	line = 0;
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	static_str = save_buffer(fd, static_str);
	line = get_line(static_str);
	static_str = get_endside(static_str);
	if ((!static_str || static_str[0] == '\0') && !*line)
	{
		free (static_str);
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}




/*
#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


char	*get_line(char *static_str)
{
	int		i;
	char	*str;

	if (!static_str)
	{
		free(static_str);
		return (NULL);
	}
	i = 0;
	while (static_str[i] && static_str[i] != '\n')
		i++;
	if (static_str[i] == '\n')
		str = (char *)malloc((i + 2) * sizeof(char));
	else
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	
	i = 0;
	while (static_str[i] && static_str[i] != '\n')
	{
		str[i] = static_str[i];
		i++;
	}
	if (static_str[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_endside(char *string)
{
	int		i;
	int		j;
	char	*end;
	
	i = 0;
	j = 0;
	if (!*string)
	{
		free(string);
		return (NULL);
	}
	while (string[i] && string[i] != '\n')
		i++;
	end = (char *)malloc(sizeof(char) * (ft_strlen(string) - i + 1));
	if (!end)
		return (NULL);
	if (string[i] == '\n')
		i++;
	while (string[i])
		end[j++] = string[i++];
	end[j] = '\0';
	free(string);
	return (end);
}

char	*save_buffer(int fd, char *static_str)
{
	char	*buffer;
	int		n_bytes;
	char	*temp;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	n_bytes = read(fd, buffer, BUFFER_SIZE);
	while (n_bytes > 0 && ft_strchr(static_str, '\n') == NULL)
	{
		if (n_bytes < 0)
		{
			free(buffer);
			free(static_str);
			return (NULL);
		}
		buffer[n_bytes] = '\0';
		if (!static_str)
		{
			static_str = (char *)malloc(1 * sizeof(char));
			static_str[0] = '\0';
		}
		temp = static_str;
		static_str = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(static_str, '\n'))
			break ;
		n_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (n_bytes <= 0)
		return (NULL);
	return (static_str);
}

char	*get_next_line(int fd)
{
	static char	*static_str;
	char		*line;

	line = NULL;
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	static_str = save_buffer(fd, static_str);
	line = get_line(static_str);
	if (!static_str || static_str[0] == '\0' || !line)
	{
		free (static_str);
		free(line);
		return (NULL);
	}
	static_str = get_endside(static_str);
	return (line);
}*/