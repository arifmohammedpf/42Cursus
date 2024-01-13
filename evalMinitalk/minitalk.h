/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtashrif <mtashrif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:54:12 by mtashrif          #+#    #+#             */
/*   Updated: 2023/12/01 15:54:13 by mtashrif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

size_t		ft_strlen(const char *s);
void		ft_putstr(char *string);
void		ft_putchar(char c);
void		ft_putnbr(int d);
int			ft_atoi(const char *str);
void		receive_message(int sig);
void		send_messege(char c, int pid);
int			ft_isalpha(char *c);

#endif
