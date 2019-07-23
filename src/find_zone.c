/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_zone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:57:23 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/23 14:14:15 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>

static size_t	*find_page(size_t *ptr, size_t *zone, size_t zsize)
{
	size_t steps;

	steps = zsize / STEP;

	while (zone)
	{
		if (ptr > zone && ptr < zone + steps)
			return (zone);
		zone = (size_t *)(zone[steps - 1]);
	}
	return (0);
}

size_t			*find_zone(size_t *ptr, size_t *zsize)
{
	size_t	*p;

	*zsize = TINY_ZONE;
	p = find_page(ptr, map.tiny, TINY_ZONE);
	if (p)
		return (p);
	*zsize = SMALL_ZONE;
	p = find_page(ptr, map.small, SMALL_ZONE);
	return (p);
}

size_t			*find_zone_large(size_t *ptr)
{
	size_t	i;
	size_t	**zone;

	i = 0;
	ptr -= 3;
	zone = map.large;
	while (i < BLK_SIZE / STEP - 1)
	{
		if (zone[i] == ptr)
			return (ptr);
		i++;
		if (i == BLK_SIZE / STEP - 1)
		{
			if (zone[i])
			{
				zone = (size_t **)zone[i];
				i = 0;
			}
		}
	}
	return (0);
}

int				valid_pointer(size_t *ptr, size_t *zone, size_t zsize)
{
	t_meta	*meta;
	size_t	i;

	i = 2;
	while (i < zsize / STEP)
	{
		meta = (t_meta *)(zone + i);
		if (ptr == (size_t *)meta + 2)
			return (1);
		i += ALIGN(meta->cap - 1) / STEP + 4;
	}
	return (0);
}
