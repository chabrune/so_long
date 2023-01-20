/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:34:00 by chabrune          #+#    #+#             */
/*   Updated: 2023/01/20 17:39:49 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*str;
	size_t	len;

	i = 0;
	len = ft_strlen_sl(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	if (ft_strchr(str, '\n'))
		str[--i] = '\0';
	else
		str[i] = '\0';
	return (str);
}

int	ft_strlen_sl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	while (*str != (char)c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

void	set_data(t_data *data, t_map map)
{
	data->map.maps = map.maps;
	data->map.x = 0;
	data->map.y = 0;
	data->check_C = 0;
	data->check_E = 0;
	data->check_P = 0;
	data->foot_count = 0;
	data->C_count = 0;
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
