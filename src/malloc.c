/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:07:26 by zfaria            #+#    #+#             */
/*   Updated: 2020/01/18 13:49:23 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <libft.h>

t_mutex	g_lock = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	void	*ptr;

	init_map();
	if (size == 0)
		return (0);
	pthread_mutex_lock(&g_lock);
	if (size <= TINY_CAP)
		ptr = find_free_mem(g_map.tiny, TINY_ZONE, size);
	else if (size <= SMALL_CAP)
		ptr = find_free_mem(g_map.small, SMALL_ZONE, size);
	else
		ptr = alloc_large(size);
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}
