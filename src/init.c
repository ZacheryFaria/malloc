/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:28:08 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/31 11:19:11 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <stdio.h>

t_map	g_map;

void	init_map(void)
{
	if (!g_map.small)
	{
		g_map.small = alloc(SMALL_ZONE);
		g_map.tiny = alloc(TINY_ZONE);
		g_map.large = alloc(BLK_SIZE);
	}
}
