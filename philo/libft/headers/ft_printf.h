/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <fleitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:56:07 by fleitz            #+#    #+#             */
/*   Updated: 2022/03/08 09:11:07 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *str, ...);
int		ft_select(char c, va_list arguments);
void	ft_putchar(int c);
int		ft_putstr(char *str);
int		ft_putnbr(int n);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_putnbr_16(unsigned int n, char c);
int		ft_putptr(intptr_t n);

#endif
