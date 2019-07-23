/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:07:26 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/23 14:23:27 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <stdio.h>

void	*malloc(size_t size)
{
	void	*ptr;

	init_map();

	if (size == 0)
		return (0);
	if (size <= TINY_CAP)
		ptr = find_free_mem(map.tiny, TINY_ZONE, size);
	else if (size <= SMALL_CAP)
		ptr = find_free_mem(map.small, SMALL_ZONE, size);
	else
		ptr = alloc_large(size);
	return (ptr);
}
