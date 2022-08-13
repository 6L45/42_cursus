/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:19:38 by mberengu          #+#    #+#             */
/*   Updated: 2021/09/24 16:19:44 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*g_arg2;

void	prog_end(int err);
char	*ft_strdup(char *src);
void	*ft_calloc(int nmemb, int size);
int		ft_atoi(const char *str);
int		ft_parsing(char *argv, int *pid);
void	ft_putnbr(long int nbr);
int		ft_isdigit(int c);

#endif
