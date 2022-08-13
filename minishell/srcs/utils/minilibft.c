/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:06:26 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/19 09:06:28 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat_dup(char *dest, char *src)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = NULL;
	res = ft_calloc(ft_strlen(dest) + ft_strlen(src) + 1, sizeof(char));
	while (dest[i])
	{
		res[i] = dest[i];
		i++;
	}
	while (src[j])
	{
		res[i + j] = src[j];
		j++;
	}
	res[i + j] = 0;
	free(dest);
	return (res);
}

void	fts_lstadd_back(t_tok **alst, t_tok *new)
{
	t_tok	*tmp;

	if (*alst == NULL)
		*alst = new;
	else
	{
		tmp = *alst;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void	*fts_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;
	size_t			i;

	ptrdst = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (dest);
	if (ptrdst > ptrsrc)
		while (len-- > 0)
			ptrdst[len] = ptrsrc[len];
	else
	{
		while (i < len)
		{
			ptrdst[i] = ptrsrc[i];
			i++;
		}
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t size, char *var)
{
	void	*new_ptr;
	int		old_size;

	if (ptr == NULL)
		return (ft_calloc(size, sizeof(char)));
	if (!size)
		return (ptr);
	old_size = mem_tracker(GET, 0, var);
	new_ptr = ft_calloc(size, sizeof(char));
	fts_memmove(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
