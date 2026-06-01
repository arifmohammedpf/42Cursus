/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_art.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:52:34 by arimoham          #+#    #+#             */
/*   Updated: 2025/09/19 15:22:45 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	display_info(void)
{
	printf("\n\033[32m");
	printf("   ·········································\n");
	printf("   ·          RAYCASTING ENGINE            ·\n");
	printf("   ·                                       ·\n");
	printf("   ·        Controls:                      ·\n");
	printf("   ·        • W/A/S/D    - Move            ·\n");
	printf("   ·        • Right/Left - Look around     ·\n");
	printf("   ·        • ESC        - Exit            ·\n");
	printf("   ·········································\n");
	printf("\033[0m\n");
}
