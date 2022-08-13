/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:50:33 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/08 06:50:38 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <string.h>

int		got_new_line(char *str);
int		file_reader(int fd, char **line);
int		get_next_line(int fd, char **line);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strjoin(char **s1, char **s2);
void	ft_strchr(char **line, int c, char **backup);
void	backup_reader(char **backup, char **line);
size_t	ft_strlen(char const *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);

#endif
