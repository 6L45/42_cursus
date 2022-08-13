/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 05:47:37 by mberengu          #+#    #+#             */
/*   Updated: 2021/12/06 15:00:20 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

# define ENV_FILE 			"./.env.txt"
# define TOKENCEPTION_VAR	"tokenception"
# define REDIR_L_SET		"redirl_set"
# define TOK_TYPE			"token_type"
# define BUFPSIZE 256
# define U_STDIN		0
# define U_STDOUT		1
# define U_STDERR		2

enum e_type
{
	CMD = 3,
	PIPE,
	QUOTE,
	D_QUOTE,
	REDIR_R,
	REDIR_L,
	HEREDOC,
	NORM,
	CREATE,
	VAR,
	SET,
	GET,
	RESET,
	FREE,
	ALL,
	ADD,
	POP,
	DELETE,
	EXIT,
	CD,
	RET,
	SIG_INT = 130,
	SIG_QUIT = 131
};

typedef struct s_heredoc
{
	int		pos;
	int		end;
	char	*key;
	char	*doc;
}				t_heredoc;

typedef struct s_mem
{
	char			*name;
	int				size;
	struct s_mem	*next;
}				t_mem;

typedef struct s_cmd
{
	int		index;
	char	**commands;
	int		src;
	int		dest;
	int		status;
}				t_cmd;

typedef struct s_lex
{
	int		i;
	char	*content;
	char	**result;
}				t_lex;

typedef struct s_tok
{
	char			*cmd;
	char			**tokens;
	int				*type;
	struct s_tok	*next;
}				t_tok;

typedef struct s_pids
{
	int				pid;
	struct s_pids	*next;
}				t_pids;

char	**g_env;

/*BUILTINS*/
/* ************************************************************************** */
/*--------------------------------------------------------------------builtins*/
void	cayday(t_cmd *cmd);
void	ekko(t_cmd *cmd);
void	pay_doubleyu_di(void);
void	ex_port(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
void	henv(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
/*-----------------------------------------------------------------------utils*/
int		export_error_case(t_cmd *cmd, int i, int j);
int		home_not_set_err(char **pwd, char **current);
int		argc_from_cmd(t_cmd *cmd);
void	print_env_export_style(char **sorted_env, int output);
/* ************************************************************************** */

/*PARSING*/
/* ************************************************************************** */
/*---------------------------------------------------------------------lexer.c*/
t_tok	*dura_lex_sed_lex(char **content);
/*--------------------------------------------------------------path_handler.c*/
char	*from_relative_path(char *cmd);
char	*file_dir(char ***address, char *commands, char *cmd, char **pwd);
char	*point_dir(char *commands, char *pwd);
char	*home_dir(char **pwd);
/*---------------------------------------------------------------------redir.c*/
int		redir_handler(char *token, t_cmd *cmd);
void	cmd_rewrite_redir(char *cmdstr);
/*---------------------------------------------------------------redirl_set.c */
int		redirl_set(char **user_entry, int i);
/*--------------------------------------------------------------token_to_cmd.c*/
int		tokens_to_cmd(t_cmd *cmd, t_tok **token);
/*--------------------------------------------------------------tokenception.c*/
char	**get_tokens(char *command, t_tok *token, int i, int j);
/*-----------------------------------------------------------------tokenizer.c*/
t_tok	*tokenizer(t_lex *lexer);
/*-------------------------------------------------------------------env_var.c*/
void	var_case(t_tok *token, int pos);
/* ************************************************************************** */

/*UTILS*/
/* ************************************************************************** */
/*--------------------------------------------------------------errors_print.c*/
void	three_part_err(char *strstart, char *cmd, char *strend, int out);
char	*no_such_file_path_handler(char *cmd, DIR **dir,
			char **pwd, char ***address);
int		no_such_file_redir(char *token);
void	too_many_args(int from);
int		syntax_error_return(int from);
/*----------------------------------------------------------------------free.c*/
void	free_token(t_tok **token);
void	ft_free_cmd(t_cmd *cmd);
void	ft_free_char_array(char **char_array);
void	free_env(void);
/*-------------------------------------------------------------------globals.c*/
char	*home_dir_loc(int status);
char	*last_error_ret(int status, int lst_err);
int		exit_or_ret(int status, int value);
int		sig_interrupted(int status);
char	*current_directory(int status);
/*------------------------------------------------------------memory_tracker.c*/
int		mem_tracker(int status, int value, char *loc);
/*-----------------------------------------------------------------minilibft.c*/
void	*ft_realloc(void *ptr, size_t size, char *var);
void	*fts_memmove(void *dest, const void *src, size_t len);
void	fts_lstadd_back(t_tok **alst, t_tok *new);
char	*ft_strcat_dup(char *dest, char *src);
/*-----------------------------------------------------------------env_utils.c*/
char	**replacement_array_plus(int size, char *var, char *value);
char	**replacement_array_minus(int size, int j);
int		find_env_var(char *var);
char	*get_env(char *var);
char	**copy_env(void);
/*----------------------------------------------------------------norminette.c*/
void	norminette_pas_du_tout(int pid, int *status);
void	norminette_a_la_folie(char ***res, char **ret_env, int *j);
void	norminette_passionnement(int j);
void	norminette_beaucoup(char *command, int *i);
void	norminette_un_peu(char ***res);
/*---------------------------------------------------------------parse_utils.c*/
char	char_spec(char actual_c);
int		enum_type_return(char *str);
int		heredoc_ret_handler(char *token, t_cmd *cmd);
int		pass_quotes(char *str);
char	*negative_return_res(char *command, int *i);
/*-------------------------------------------------------------lst_min_utils.c*/
char	*not_a_directory(DIR **dir, char **pwd, char *cmd, char ***address);
char	*env_var_res(char *command, int k, int *i);
int		last_min_patch(int status, int value);
void	execve_error_exits(t_cmd *cmd, char *tmp_seek_cmd);
/*---------------------------------------------------------------------utils.c*/
int		contain_char(char *str, char c);
char	*str_char_cat(char *buf, char c);
int		ft_strchr_str(const char *s, const char *seek);
int		pwd_res(char **pwd, char *commands, int match);
int		only_cd_case(char **pwd, char **current);
/* ************************************************************************** */

/*SRCS*/
/* ************************************************************************** */
/*--------------------------------------------------------builtins_processes.c*/
void	to_builtins(t_cmd *cmd, int i, int fd[2], int old_fd[2]);
/*-------------------------------------------------------------child_process.c*/
void	child_process(t_cmd *cmd);
/*-----------------------------------------------------------------------env.c*/
void	g_env_modif(int status, char *var, char *value, char **new_env);
/*------------------------------------------------------------------exec_cmd.c*/
void	cmds_buisness(char *user_entry, t_tok **token);
/*------------------------------------------------------------fork_processes.c*/
void	to_fork(t_cmd *cmd, int i, int fd[2], int old_fd[2]);
/*-----------------------------------------------------------heredoc_handler.c*/
int		heredoc_handler(char *token, t_cmd *cmd);
/*------------------------------------------------------------------multipex.c*/
void	multipex(t_cmd *cmd, int i, int old_fd[2]);
/*--------------------------------------------------------------------prompt.c*/
void	prompt(void);
void	write_g_env(char **env);
/*-------------------------------------------------------------------signals.c*/
void	ft_receive_sig(int signal);
void	ft_receive_sig_after_fork(int signal);
void	rl_replace_line(const char *text, int clear_undo);
/* ************************************************************************** */

#endif
