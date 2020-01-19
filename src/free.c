/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:43:53 by zfaria            #+#    #+#             */
/*   Updated: 2020/01/18 14:41:49 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <sys/mman.h>
#include <stdio.h>

t_mutex	g_lock;

void	free_large(size_t *ptr)
{
	t_metalrg	*meta;
	int			res;

	meta = (t_metalrg *)ptr;
	*meta->back = 0;
	res = munmap(ptr, meta->meta.cap);
	if (res == -1)
		return ;
}

void	defrag_next(t_meta *head)
{
	t_meta	*next_head;
	t_meta	*next_foot;
	size_t	total_bytes;

	next_head = (void *)head + head->cap + sizeof(t_meta) * 2;
	if (next_head->cap == 0)
	{
		head->cap = 0;
		return ;
	}
	if (ISFREE(next_head))
	{
		total_bytes = head->cap;
		next_foot = (void *)next_head + next_head->cap + sizeof(t_meta);
		total_bytes += next_foot->cap + sizeof(t_meta) * 2;
		head->cap = total_bytes;
		head->req = 0;
		next_foot->cap = total_bytes;
		next_foot->req = 0;
	}
}

void	defrag_prev(t_meta *head)
{
	t_meta	*prev_foot;
	t_meta	*prev_head;
	t_meta	*foot;
	size_t	total_bytes;

	foot = (void *)head + head->cap;
	prev_foot = (void *)head - sizeof(t_meta);
	if (prev_foot->req == (size_t)-1)
		return ;
	prev_head = (void *)prev_foot - prev_foot->cap - sizeof(t_meta);
	if (ISFREE(prev_head))
	{
		if (head->cap == 0)
		{
			prev_head->cap = 0;
			return ;
		}
		total_bytes = prev_head->cap + head->cap + sizeof(t_meta) * 2;
		prev_head->cap = total_bytes;
		prev_head->req = 0;
		foot->cap = total_bytes;
		foot->req = 0;
	}
}

void	free_internal(size_t *ptr)
{
	t_meta	*head;
	t_meta	*foot;

	head = (t_meta *)(ptr - 2);
	head->cap ^= 1;
	foot = (t_meta *)(ptr + head->cap / STEP);
	foot->cap ^= 1;
}

void	free(void *ptr)
{
	size_t	*zone;
	size_t	zsize;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_lock);
	zone = find_zone_large(ptr);
	if (zone)
		free_large(zone);
	else
	{
		zone = find_zone(ptr, &zsize);
		if (!valid_pointer(ptr, zone, zsize))
			;
		else
			free_internal(ptr);
	}
	pthread_mutex_unlock(&g_lock);
}
