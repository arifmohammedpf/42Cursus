/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 07:59:28 by arimoham          #+#    #+#             */
/*   Updated: 2024/01/28 08:37:25 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>

int		ft_isalpha(char *str);
void	ft_putchar(char c);
void	ft_putstr(char *s);
int		ft_atoi(const char *str);
void	ft_putnbr(int d);
void	get_signal(int signal);
void	send_char(char c, int pid);

#endif
