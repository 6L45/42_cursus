/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 05:42:13 by mberengu          #+#    #+#             */
/*   Updated: 2021/12/06 14:38:29 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_cd_case(char **pwd, char **current)
{
	char	*home;

	home = get_env("HOME");
	if (!home)
	{
		free(home);
		return (home_not_set_err(pwd, current));
	}
	free(home);
	(*pwd) = home_dir(pwd);
	return (1);
}

int	pwd_res(char **pwd, char *commands, int match)
{
	if (((*pwd)[ft_strlen((*pwd)) - 1] != '/'))
		(*pwd) = ft_strcat_dup((*pwd), "/");
	(*pwd) = ft_strcat_dup((*pwd), commands);
	return (match);
}

int	ft_strchr_str(const char *s, const char *seek)
{
	int				i;
	int				j;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	j = 0;
	s1 = (unsigned char *)s;
	s2 = (unsigned char *)seek;
	while (s1[i])
	{
		while (s1[i + j] == s2[j])
		{
			if (!s2[j] && !s1[i + j])
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

char	*str_char_cat(char *buf, char c)
{
	size_t	buflen;
	char	*str;
	size_t	i;

	i = 0;
	buflen = ft_strlen(buf);
	str = (char *)ft_calloc((buflen + 2), sizeof(char));
	while (i < buflen)
	{
		str[i] = buf[i];
		i++;
	}
	str[buflen] = c;
	str[buflen + 1] = '\0';
	free(buf);
	return (str);
}

int	contain_char(char *str, char c)
{
	if (!str || !c)
		return (0);
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}
