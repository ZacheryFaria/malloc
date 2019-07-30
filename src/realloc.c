/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:22:21 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/30 12:56:21 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <stdio.h>
#include <signal.h>

static void	*adjust_mem(size_t *ptr, size_t size)
{
	t_meta	*meta;
	void	*newptr;

	meta = (t_meta *)(ptr - 2);
	if (meta->cap - 1 >= size)
	{
		meta->req = size;
		return (ptr);
	}
	else
	{
		newptr = malloc(size);
		memcpy(newptr, ptr, meta->req);
		free(ptr);
		return (newptr);
	}
}

static void	*adjust_large(size_t *ptr, size_t size)
{
	t_metalrg	*meta;
	void		*newptr;

	meta = (t_metalrg *)(ptr - 3);
	if (meta->meta.cap - 1 >= size)
	{
		meta->meta.req = size;
		return (ptr);
	}
	else
	{
		newptr = malloc(size);
		memcpy(newptr, ptr, meta->meta.req);
		free(ptr);
		return (newptr);
	}
}

void		*realloc(void *ptr, size_t size)
{
	size_t	*zone;
	size_t	zsize;

	if (!ptr)
		return (malloc(size));
	if (!size && ptr)
	{
		free(ptr);
		return (0);
	}
	zone = find_zone_large(ptr);
	if (zone)
		return adjust_large(ptr, size);
	else
	{	
		zone = find_zone(ptr, &zsize);
		if (!valid_pointer(ptr, zone, zsize))
			return (0);
		return (adjust_mem(ptr, size));
	}
}
