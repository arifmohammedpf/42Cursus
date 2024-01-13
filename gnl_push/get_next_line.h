/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:49:26 by arimoham          #+#    #+#             */
/*   Updated: 2023/12/16 12:05:15 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*save_after_nl(char *curr_buffer);
char	*save_new_line(char *curr_buffer);
char	*read_buffer(char *curr_buff, char *tmp_buffer, int fd, ssize_t *byte);
char	*read_buffer_line(char *curr_buffer, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(char const *str);
char	*ft_strchr(char const *str, int character);
char	*ft_strdup(char const *src);

#endif