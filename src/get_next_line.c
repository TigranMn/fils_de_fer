/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:14:03 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/05/27 14:07:21 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (0);
}

char	*reset_buffer(char *buffer)
{
	char	*resetted;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	resetted = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!resetted)
		return (NULL);
	j = 0;
	i++;
	while (buffer[i])
		resetted[j++] = buffer[i++];
	resetted[j] = '\0';
	free(buffer);
	return (resetted);
}

char	*ft_line(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = malloc(sizeof(char) * i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_read(int fd, char *buffer)
{
	char	buff[BUFFER_SIZE + 1];
	int		read_bytes;

	*buff = 0;
	read_bytes = 1;
	while (!ft_strchr(buff, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			if (buffer)
				free(buffer);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		if (!buffer)
			buffer = ft_strdup(buff);
		else
		{
			buffer = ft_strjoin(buffer, buff);
		}
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[10000];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = reset_buffer(buffer[fd]);
	return (line);
}
