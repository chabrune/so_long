/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 06:54:16 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/20 15:14:53 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = ft_read(fd, stash);
	if (!stash)
	{
		free(stash);
		stash = NULL;
		return (0);
	}
	line = ft_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (0);
	}
	stash = ft_save(stash);
	return (line);
}

char	*ft_read(int fd, char *stash)
{
	char	*buff;
	int		readed;

	readed = 1;
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (ft_free(stash));
	while (readed > 0 && (!ft_strchr_gnl(stash, '\n')))
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed < 0)
		{
			ft_free(stash);
			return (ft_free(buff));
		}
		buff[readed] = '\0';
		stash = ft_strjoin_gnl(stash, buff);
		if (!stash)
			return (ft_free(buff));
	}
	ft_free(buff);
	return (stash);
}

char	*ft_line(char *stash)
{
	int		i;
	char	*buff;

	i = 0;
	if (!stash[i] || !stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (ft_strchr_gnl(stash, '\n'))
		buff = (char *)malloc((i + 2) * sizeof(char));
	else
		buff = (char *)malloc((i + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	i = -1;
	while (stash[++i] && stash[i] != '\n')
		buff[i] = stash[i];
	if (stash[i] == '\n')
	{
		buff[i] = stash[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

char	*ft_save(char *stash)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash || !stash[i])
		return (ft_free(stash));
	if (stash[i] == '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (ft_strlen_gnl(stash) - i + 1));
	if (!s)
		return (ft_free(stash));
	j = 0;
	while (stash[i])
		s[j++] = stash[i++];
	s[j] = '\0';
	ft_free(stash);
	return (s);
}

void	*ft_free(char *s1)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (NULL);
}
