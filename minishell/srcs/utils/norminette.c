/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:59:14 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/29 16:59:16 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norminette_un_peu(char ***res)
{
	(*res) = ft_calloc(1, sizeof(char));
	mem_tracker(SET, 1 * sizeof(char), TOKENCEPTION_VAR);
	mem_tracker(SET, 1 * sizeof(int *), TOK_TYPE);
}

void	norminette_beaucoup(char *command, int *i)
{
	while (command[*i] && (command[*i] > 0 && command[*i] <= 32))
		*i += 1;
}

void	norminette_passionnement(int j)
{
	mem_tracker(SET, sizeof(char **) * (j + 2), TOKENCEPTION_VAR);
	mem_tracker(SET, sizeof(int *) * (j + 2), TOK_TYPE);
}

void	norminette_a_la_folie(char ***res, char **ret_env, int *j)
{
	int		k;
	char	**ret_array;

	k = 0;
	ret_array = ft_split((*ret_env), ' ');
	free((*ret_env));
	while (ret_array[k])
		k++;
	ft_free_char_array((*res));
	(*res) = ft_calloc(k + 1, sizeof(char *));
	mem_tracker(SET, k + 1, TOKENCEPTION_VAR);
	k = 0;
	while (ret_array[k])
	{
		(*res)[k] = ft_strdup(ret_array[k]);
		k++;
	}
	ft_free_char_array(ret_array);
	*j += k;
}

void	norminette_pas_du_tout(int pid, int *status)
{
	waitpid(pid, status, 0);
	signal(SIGINT, ft_receive_sig);
	signal(SIGQUIT, SIG_IGN);
}
