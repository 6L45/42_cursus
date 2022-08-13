#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_flags
{
	int		f;
	int		minus;
	int		zero;
	short	has_width;
	int		width;
	short	has_preci;
	int		preci;
	int		size;
}				t_flags;

/*ft_printf.c -----------------------------------------------------------*/
int		ft_printf(const char *format, ...);
void	str_print(char *str, t_flags *card, va_list ap);
int		flag_substitute(t_flags *card, char *str, va_list ap);
void	arg_parsing(t_flags *card, va_list ap);
void	args_inti(t_flags *card);
/*-----------------------------------------------------------------------*/

/*flag_reader.c----------------------------------------------------------*/
void	flag_reader(t_flags *card, char *str, va_list ap);
int		f_reader_postpoint(t_flags *card, char *str, va_list ap);
int		f_reader_prepoint(t_flags *card, char *str, va_list ap);
/*-----------------------------------------------------------------------*/

/*chars_flag.c-----------------------------------------------------------*/
void	ft_put_s(t_flags *card, va_list ap);
int		putlen_chars(t_flags *card, char *s);
void	ft_putstrl(char *str, int len, t_flags *card);
void	ft_putstr_card(char *str, t_flags *card);
void	ft_put_c(t_flags *card, va_list ap);
/*-----------------------------------------------------------------------*/

/*int_flag.c-------------------------------------------------------------*/
void	ft_put_d(t_flags *card, va_list ap);
int		putlen(t_flags *card, long int arg, int *padding);
void	width_putchar(t_flags *card, int len, int i, long int *arg);
void	ft_puti(long int arg, int padding, t_flags *card);
int		ft_get_digits(int nbr);
/*-----------------------------------------------------------------------*/

/*x_flag.c---------------------------------------------------------------*/
void	ft_put_x(t_flags *card, va_list ap);
int		putlen_x(t_flags *card, unsigned int arg, int *padding, int *maj);
void	ft_putx(unsigned int arg, int padding, int maj, t_flags *card);
int		ft_get_digits_x(unsigned int nb);
/*-----------------------------------------------------------------------*/

/*utils.c----------------------------------------------------------------*/
int		ft_atoi(const char *str);
int		ft_strchri(const char *s, char c);
int		ft_isdigit(char c);
int		ft_strlen(char *str);
void	ft_putchar(char c, t_flags *card);
/*-----------------------------------------------------------------------*/

/*u_flag.c---------------------------------------------------------------*/
void	ft_put_u(t_flags *card, va_list ap);
int		putlen_u(t_flags *card, unsigned int arg, int *padding);
void	ft_putu(unsigned int arg, int padding, t_flags *card);
int		ft_get_digits_u(int nbr);
/*-----------------------------------------------------------------------*/

/*p_flag.c---------------------------------------------------------------*/
void	ft_put_p(t_flags *card, va_list ap);
int		putlen_p(t_flags *card, unsigned long int arg, int *padding);
void	unsigned_width_putchar(t_flags *card, int len, int i);
void	ft_putp(unsigned long int arg, int padding, t_flags *card);
int		ft_get_digits_p(unsigned long int nb);
/*-----------------------------------------------------------------------*/

#endif
