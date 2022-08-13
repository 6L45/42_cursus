/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:58:43 by mberengu          #+#    #+#             */
/*   Updated: 2021/03/24 09:58:45 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*resf;
	t_list	*toreturn;

	toreturn = NULL;
	while (lst)
	{
		resf = ft_lstnew(f(lst->content));
		if (!resf)
		{
			ft_lstclear(&lst, del);
			if (toreturn)
				ft_lstclear(&toreturn, del);
			break ;
		}
		ft_lstadd_back(&toreturn, resf);
		lst = lst->next;
	}
	return (toreturn);
}
