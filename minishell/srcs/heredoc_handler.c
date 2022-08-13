/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:18:02 by mberengu          #+#    #+#             */
/*   Updated: 2021/12/07 11:18:03 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key_word(char *token)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (token[i] && token[i] == '<')
		i++;
	if (token[i] == '-')
		i++;
	while (token[i] && token[i] > 0 && token[i] <= 32)
		i++;
	while (token[i + j] && !(token[i + j] > 0 && token[i + j] <= 32))
		j++;
	return (ft_strndup(&token[i], j));
}

static char	*rdoc_swap_str_buisness(char *new_entry, char *readl_res)
{
	char	*swap;

	if (new_entry)
		swap = ft_strjoin(new_entry, "\n");
	else
		swap = ft_strdup(new_entry);
	free(new_entry);
	new_entry = ft_strjoin(swap, readl_res);
	free(readl_res);
	free(swap);
	return (new_entry);
}

void	close_heredoc(char **new_entry, char **readl_res, int fd)
{
	if (*new_entry)
	{
		(*new_entry) = str_char_cat((*new_entry), '\n');
		ft_putstr_fd((*new_entry), fd);
	}
	free((*readl_res));
	free(*new_entry);
	exit(0);
}

static void	send_the_doc(char *key, int fd)
{
	int		err_line;
	char	*new_entry;
	char	*readl_res;

	new_entry = NULL;
	err_line = 1;
	while (1)
	{
		readl_res = readline("> ");
		if (readl_res)
		{
			if (!ft_strcmp(readl_res, key))
				close_heredoc(&new_entry, &readl_res, fd);
			new_entry = rdoc_swap_str_buisness(new_entry, readl_res);
			err_line++;
		}
		else
		{
			write(2, "-bash: warning: here-document at line ", 38);
			ft_putnbr_fd(err_line, 2);
			three_part_err(" delimited by end-of-file (wanted `", key, "')", 2);
			close_heredoc(&new_entry, &readl_res, fd);
		}
	}
}

int	heredoc_handler(char *token, t_cmd *cmd)
{
	int		pid;
	int		fd[2];
	int		status;
	char	*key;

	if (cmd->src)
		close(cmd->src);
	pipe(fd);
	signal(SIGINT, ft_receive_sig_after_fork);
	signal(SIGQUIT, ft_receive_sig_after_fork);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		key = get_key_word(token);
		close(fd[0]);
		send_the_doc(key, fd[1]);
	}
	close(fd[1]);
	norminette_pas_du_tout(pid, &status);
	cmd->src = fd[0];
	if (WEXITSTATUS(status) == 2 || sig_interrupted(GET))
		return (0);
	return (1);
}
