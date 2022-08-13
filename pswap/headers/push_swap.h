/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:54:54 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:54:55 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef enum e_act
{
	PA = 11,
	PB = 12,
	SA = 21,
	SB = 22,
	SS = 20,
	RA = 31,
	RB = 32,
	RR = 30,
	RRA = 41,
	RRB = 42,
	RRR = 40
}				t_act;

typedef struct s_pos
{
	short	swap_a;
	short	swap_b;
	short	up_a;
	short	up_b;
	short	down_a;
	short	down_b;
	short	a_to_b;
	short	b_to_a;
	int		obj_a;
	int		obj_b;
	int		max;
	int		min;
	int		last_a;
	int		last_b;
	int		size;
	int		median;
}				t_pos;

typedef struct s_list
{
	int				nb;
	struct s_list	*next;
}				t_list;

/*act_pswap------------------------------------------------------------------*/
/*01----------*/
void		pa(t_list **lst1, t_list **lst2, t_list **actions);
void		pb(t_list **lst1, t_list **lst2, t_list **actions);
void		rr(t_list **lst1, t_list **lst2, t_list **actions);
void		rrr(t_list **lst1, t_list **lst2, t_list **actions);
/*02----------*/
void		ra(t_list **lst1, t_list **actions, short rr);
void		rb(t_list **lst2, t_list **actions, short rr);
void		rra(t_list **lst1, t_list **actions, short rrr);
void		rrb(t_list **lst2, t_list **actions, short rrr);
/*03----------*/
void		sa(t_list **lst1, t_list **actions, short ss);
void		sb(t_list **lst2, t_list **actions, short ss);
void		ss(t_list **lst1, t_list **lst2, t_list **actions);
/*---------------------------------------------------------------------------*/

/*errors_entry_checker.c-----------------------------------------------------*/
int			arg_checker(int argc, char **str);
int			no_duplicate(t_list **lst);
/*---------------------------------------------------------------------------*/

/*indexed_list.c-------------------------------------------------------------*/
void		new_min(t_list **params_receiver, t_list **lst1, int prev);
void		next_min_init(t_list **params_receiver, int nb, int *prev,
				int *new);
void		stack_order(t_list **params_receiver, t_list **lst1, t_pos *pos);
void		stack_min_max(t_list **params_receiver, t_list **lst1, t_pos *pos);
t_list		*lst_crea_argsize(t_list **params_receiver, t_pos *pos);
/*---------------------------------------------------------------------------*/

/*minlibft.c-----------------------------------------------------------------*/
int			ft_lstsize(t_list *lst);
t_list		*ft_lstnew(int nbr);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_isdigit(int c);
/*custom---*/
long int	ft_atoi_custom(const char *str, int *j);
/*---------------------------------------------------------------------------*/

/*mvt_handler.c--------------------------------------------------------------*/
/*01----------*/
int			first_under_median(t_list **lst1, t_pos *pos);
int			last_under_median(t_list **lst1, t_pos *pos);
int			mvt_to_first(int first_pos, int lstsize);
int			mvt_to_last(int last_pos, int lstsize);
int			mvt_handler(int first_pos, int last_pos, int lstsize, int *f1_l0);
/*02----------*/
void		mvt_to_top(t_list **lst1, t_list **lst2, t_pos *pos,
				t_list **actions);
void		direction_handler(t_pos *pos, int position, int lstsize);
void		set_mvt_to_the_closest_under_median_nb(t_list **lst1, t_pos *pos);
/*---------------------------------------------------------------------------*/

/*pswap.status.c-------------------------------------------------------------*/
int			last_mvt(t_list **actions);
int			swap_lst2_status(t_list **lst2, t_pos *pos, t_list **actions);
int			swap_lst1_status(t_list **lst1, t_pos *pos, t_list **actions);
/*---------------------------------------------------------------------------*/

/*reorganize.c---------------------------------------------------------------*/
void		set_mvt_lst2(t_list **lst2, t_pos *pos);
void		set_mvt_lst1(t_list **lst1, t_pos *pos);
void		lst1_order(t_list **lst1, t_list **lst2, t_pos *pos,
				t_list **actions);
void		mvt_max_top_lst2(t_list **lst2, t_pos *pos, t_list **actions);
void		set_order(t_list **lst1, t_list **lst2, t_pos *pos,
				t_list **actions);
/*---------------------------------------------------------------------------*/

/*solver.c-------------------------------------------------------------------*/
int			median_is(t_list **lst1, t_pos *pos);
int			there_are_under_median_nb(t_list **lst1, t_pos *pos);
int			lst1_is_ordered(t_list **lst1, t_pos *pos);
void		solver(t_list **lst1, t_list **lst2, t_pos *pos,
				t_list **actions);
/*---------------------------------------------------------------------------*/

/*utils.c--------------------------------------------------------------------*/
void		t_pos_init(t_pos *pos);
/*indexed_list*/
void		lst_min_max_size(t_list **params_receiver, t_pos *pos);
t_list		*list_from_params(int argc, char **str);
/*main--------*/
void		lsts_init(t_list **params_receiver,
				t_list **lst1, t_list **lst2, t_list **actions);
void		t_list_free(t_list *lst);
void		actions_if_forest(int act);
void		lsts_free(t_list *params, t_list *lst1, t_list *lst2,
				t_list *actions);
void		actions_print(t_list *actions);
/*mvt_handler-*/
int			int_pos(t_list **lst1);
float		find_min(t_list **lst1, t_pos *pos);
float		find_max(t_list **lst1);
/*solver------*/
int			vertical_check_pos(t_list **lst1, int nb);
void		swp_handler(t_list **lst1, t_list **lst2, t_pos *pos,
				t_list **actions);
void		mouvement_lst1(t_list **lst1, t_list **lst2, t_pos *pos,
				t_list **actions);
void		with_lst2(t_list **lst1, t_list **lst2, t_pos *pos,
				t_list **actions);
int			there_is_first_chunk_only(t_list **lst2);
/*---------------------------------------------------------------------------*/
void		mvt_review(t_list **actions);
void		w_error(void);

#endif
