/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:25:07 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/31 11:26:48 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>

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

void	set_meta(size_t *zone, size_t req, size_t i)
{
	t_meta *meta;

	meta = (t_meta *)(zone + i);
	meta->cap = ALIGN(req);
	meta->req = req;
	meta->cap |= 1;
	memcpy(zone + i + 2 + ALIGN(req) / sizeof(size_t), meta, sizeof(t_meta));
}

void	*find_free_mem(size_t *zone, size_t zsize, size_t req)
{
	size_t		i;
	size_t		steps;
	t_meta		*meta;

	steps = zsize / sizeof(size_t);
	i = 2;
	while (i < steps)
	{
		meta = (t_meta *)(zone + i);
		if (ISFREE(meta))
		{
			if (meta->cap == 0)
			{
				if (steps - i - 6 > (ALIGN(req) / sizeof(size_t)))
				{
					set_meta(zone, req, i);
					return (zone + i + 2);
				}
				break;
			}
			else if (meta->cap >= ALIGN(req))
			{
				meta->req = req;
				meta->cap |= 1;
				meta = (t_meta *)(zone + i + (meta->cap / STEP) + 2);
				meta->req = req;
				meta->cap |= 1;
				return (zone + i + 2);
			}
			else
			{
				i += (meta->cap / sizeof(size_t)) + 4;
				continue;
			}
		}
		else
		{
			i += (meta->cap - 1) / sizeof(size_t) + 4;;
			continue;
		}
		i++;
	}
	if (zone[steps - 1] == 0)
	{
		zone[steps - 1] = (size_t)alloc(zsize);
		size_t *s = (size_t *)zone[steps - 1];
		s[0] = (size_t)zone;
	}
	return (find_free_mem((size_t *)zone[steps - 1], zsize, req));
}

size_t	**find_large_ptr(size_t **zone)
{
	size_t	i;

	i = 0;
	while (i < BLK_SIZE / STEP - 1)
	{
		if (zone[i] == 0)
			return (&zone[i]);
		i++;
	}
	if (!zone[i])
		zone[i] = alloc(BLK_SIZE);
	return (find_large_ptr((size_t **)zone[i]));
}

void	*alloc_large(size_t req)
{
	size_t	bytes;
	size_t	*ptr;
	t_metalrg	*meta;

	bytes = req + (sizeof(t_metalrg));
	bytes = ALIGN_LARGE(bytes);
	ptr = alloc(bytes);
	if (!ptr)
		return (0);
	meta = (t_metalrg *)ptr;
	meta->meta.cap = bytes - sizeof(t_metalrg);
	meta->meta.req = req;
	meta->back = find_large_ptr(g_map.large);
	*meta->back = ptr;
	return (ptr + 3);
}
