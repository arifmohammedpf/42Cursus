/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:05:11 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/24 20:50:28 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

int		ft_printf(const char *str, ...);
int		print_arg(char *str, va_list *args);
int		ft_print_str(char *str_arg);
int		ft_print_char(char c_arg);
int		ft_print_nbr(int nbr_arg);
int		ft_print_pointer(size_t ptr_arg);
int		ft_print_hexa_decimal(unsigned int nbr_arg, char x);
int		ft_print_unsigned_decimal(unsigned int nbr_arg);

#endif