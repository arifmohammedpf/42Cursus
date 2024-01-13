/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:05:29 by arimoham          #+#    #+#             */
/*   Updated: 2023/11/14 17:03:56 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c <= '9' && c >= '0')
		|| (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// int main(void)
// {
//     printf("%d\n", ft_isalnum('a'));
//     printf("%d\n", ft_isalnum('5'));
//     printf("%d\n", ft_isalnum(' '));
//     printf("%d\n", ft_isalnum('@'));
//     return 0;
// }