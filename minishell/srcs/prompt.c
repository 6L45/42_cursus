/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:28:37 by mberengu          #+#    #+#             */
/*   Updated: 2022/01/24 12:28:39 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_g_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		g_env[i] = ft_strdup(env[i]);
		i++;
	}
}

static void	im_out(void)
{
	printf("exit\n");
	ft_free_char_array(g_env);
	clear_history();
	exit(0);
}

static int	empty_cmd(char *user_entry)
{
	int	i;

	i = 0;
	while (user_entry[i] && (user_entry[i] > 0 && user_entry[i] <= 32))
		i++;
	if (!user_entry[i])
		return (1);
	return (0);
}

void	prompt(void)
{
	char	*user_entry;
	t_tok	*token;

	while (1)
	{
		user_entry = readline("minishell : ");
		if (user_entry && !empty_cmd(user_entry))
		{
			add_history(user_entry);
			token = dura_lex_sed_lex(&user_entry);
			if (token)
				cmds_buisness(user_entry, &token);
			if (sig_interrupted(GET))
				last_error_ret(SET, sig_interrupted(GET));
			sig_interrupted(RESET);
		}
		else if (!user_entry)
			im_out();
		free(user_entry);
	}
}
