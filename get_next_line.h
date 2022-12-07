/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 06:54:50 by chabrune          #+#    #+#             */
/*   Updated: 2022/12/06 14:29:07 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
int		ft_strchr(char *s, int c);
char	*get_next_line(int fd);
char	*ft_read(int fd, char *stash);
char	*ft_line(char *stash);
char	*ft_save(char *stash);
void	*ft_free(char *s1);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t num, size_t size);

#endif