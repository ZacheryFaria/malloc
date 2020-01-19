/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:25:07 by zfaria            #+#    #+#             */
/*   Updated: 2020/01/19 12:40:47 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <libft.h>

void	*alloc(size_t size)
{
	void	*ptr;
	t_meta	*meta;

	ptr = mmap(0, size, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED)
		return (0);
	meta = ptr;
	meta->cap = -1;
	meta->req = -1;
	return (ptr);
}

size_t	*set_meta(size_t *zone, size_t req, size_t i)
{
	t_meta *meta;

	meta = (t_meta *)(zone + i);
	meta->cap = ALIGN(req);
	meta->req = req;
	meta->cap |= 1;
	ft_memcpy(zone + i + 2 + ALIGN(req) / sizeof(size_t), meta, sizeof(t_meta));
	return (zone);
}

size_t	*reset_meta(size_t *zone, size_t req, size_t i, t_meta *meta)
{
	meta->req = req;
	meta->cap |= 1;
	meta = (t_meta *)(zone + i + (meta->cap / STEP) + 2);
	meta->req = req;
	meta->cap |= 1;
	return (zone + i + 2);
}

void	*find_free_mem(size_t *zone, size_t zsize, size_t req)
{
	size_t		i;
	t_meta		*meta;

	i = 1;
	while (++i < STEPS(zsize))
	{
		meta = (t_meta *)(zone + i);
		if (ISFREE(meta))
		{
			if (meta->cap == 0)
			{
				if (STEPS(zsize) - i - 6 > (ALIGN(req) / STEP))
					return (set_meta(zone, req, i) + i + 2);
				break ;
			}
			else if (meta->cap >= ALIGN(req))
				return (reset_meta(zone, req, i, meta));
		}
		i += (meta->cap - (ISFREE(meta) ? 0 : 1)) / STEP + 3;
	}
	if (zone[STEPS(zsize) - 1] == 0)
		zone[STEPS(zsize) - 1] = (size_t)alloc(zsize);
	return (find_free_mem((size_t *)zone[STEPS(zsize) - 1], zsize, req));
}
