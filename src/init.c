/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:28:08 by zfaria            #+#    #+#             */
/*   Updated: 2019/08/01 11:27:15 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <stdio.h>

t_map	g_map;
t_mutex	g_lock;

void	init_map(void)
{
	if (!g_map.small)
	{
		g_map.small = alloc(SMALL_ZONE);
		g_map.tiny = alloc(TINY_ZONE);
		g_map.large = alloc(BLK_SIZE);
	}
}
