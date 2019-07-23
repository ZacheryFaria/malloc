/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:28:08 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/23 13:01:20 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <stdio.h>

t_map map;

void	init_map(void)
{
	if (!map.small)
	{
		map.small = alloc(SMALL_ZONE);
		map.tiny = alloc(TINY_ZONE);
		map.large = alloc(BLK_SIZE);
	}
}
