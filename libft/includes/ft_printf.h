/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:32:45 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/04 01:16:31 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifdef __linux__
#  ifndef IS_LINUX
#   define IS_LINUX 1
#  endif
#  ifndef S_EMPTY
#   define S_EMPTY "(null)"
#  endif
#  ifndef S_EMPTY_L
#   define S_EMPTY_L 6
#  endif
#  ifndef P_EMPTY
#   define P_EMPTY "(nil)"
#  endif
#  ifndef P_EMPTY_L
#   define P_EMPTY_L 5
#  endif
# else
#  ifndef IS_LINUX
#   define IS_LINUX 0
#  endif
#  ifndef S_EMPTY
#   define S_EMPTY "(null)"
#  endif
#  ifndef S_EMPTY_L
#   define S_EMPTY_L 6
#  endif
#  ifndef P_EMPTY
#   define P_EMPTY "0x0"
#  endif
#  ifndef P_EMPTY_L
#   define P_EMPTY_L 3
#  endif
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <limits.h>

typedef struct s_prefix
{
	int		is_left;
	int		is_sign;
	int		is_space;
	int		is_preceed;
	int		is_iszero;
	int		width;
	int		precision;
	int		is_precision;
}	t_prefix;

int		ft_printf(const char *fmt, ...);

char	*ft_appendfmt(char *buff, char *ptr, int *len, va_list ap);
size_t	ft_flgchk(char *ptr);
size_t	ft_specchk(char *ptr);
size_t	ft_widthchk(char *ptr);
size_t	ft_precisechk(char *ptr);
void	ft_freeprefix(t_prefix *t_pf);
int		ft_is_left(char *ptr, t_prefix *t_pf);
int		ft_is_sign(char *ptr, t_prefix *t_pf);
int		ft_is_space(char *ptr, t_prefix *t_pf);
int		ft_is_iszero(char *ptr, t_prefix *t_pf);
int		ft_is_preceed(char *ptr, t_prefix *t_pf);
int		ft_is_width(char *ptr, t_prefix *t_pf, va_list ap);
int		ft_is_precision(char *ptr, t_prefix *t_pf, va_list ap);
size_t	ft_myatoi_format(char *ptr, t_prefix *t_pf, int is_prec);

char	*ft_freemem(char *ptr);
char	*ft_mycalloc(size_t size, size_t len, char c);
char	*ft_mymemjoin(char *s1, char *s2, size_t len1, size_t len_t);

size_t	ft_nbrcnt(char *ptr);
size_t	ft_nbrsize(ssize_t n, ssize_t len);
size_t	ft_nbrusize_base(size_t n, size_t len, size_t b);
char	*ft_basenumber(int base);
char	*ft_print_nbr(ssize_t n, char *buff);
char	*ft_print_nbru_b(unsigned long long num, char *buff, int b, int shift);

char	*ft_append2str(char *buff, char c);
char	*ft_appendchr(char *buff, char *ptr, int *len);
char	*ft_append2str_ul(char *buff, char c, int shift);

char	*ft_mysubstr(char *s, unsigned int start, size_t len);
char	*ft_mystrjoin(char *s1, char *s2, int free_s1, int free_s2);

char	*ft_print_c(va_list ap, int *len, t_prefix *t_pf);
char	*ft_append_c(char *p_buff, t_prefix *t_pf, int *len);

char	*ft_print_d(va_list ap, int *len, t_prefix *t_pf);
char	*ft_print_d_2(ssize_t num, t_prefix *t_pf);
char	*ft_append_d(char *p_buff, t_prefix *t_pf, size_t len, ssize_t num);
char	*ft_append_d_2(char *p_buff, t_prefix *t_pf, size_t len, ssize_t num);
char	*ft_append_d_3(char *p_buff, t_prefix *t_pf, char *wbuff, ssize_t num);

char	*ft_print_p(va_list ap, int *len, t_prefix *t_pf);
char	*ft_append_p(char *p_buff, t_prefix *t_pf);

char	*ft_print_s(va_list ap, int *len, t_prefix *t_pf);
char	*ft_print_s2(char *buff, t_prefix *t_pf);

char	*ft_print_u(va_list ap, int *len, t_prefix *t_pf);
char	*ft_append_u(char *p_buff, t_prefix *t_pf);

char	*ft_print_x(va_list ap, int is_shift, t_prefix *t_pf, int *len);
char	*ft_append_x(char *p_buff, t_prefix *t_pf, int up, unsigned int n);
char	*ft_append_x_2(char *p_buff, t_prefix *t_pf, int up, unsigned int n);
char	*ft_append_zx(char *buff, t_prefix *t_pf, int up, unsigned int num);

#endif
