/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:23:22 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/30 10:42:56 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>

size_t	print_zone(size_t *zone, size_t zone_size)
{
	size_t		i;
	size_t		total_bytes;
	t_meta	*meta;
	size_t		steps;

	i = 2;
	steps = zone_size / sizeof(size_t);
	total_bytes = 0;
	while (i < steps - 1)
	{
		meta = (t_meta *)(zone + i);
		if (!ISFREE(meta))
		{
			printf("%p - %p : %lld bytes\n", zone + i + 2, zone + i + 2 + (meta->cap / sizeof(size_t)), meta->req);
			total_bytes += meta->req;
			i += ((meta->cap - 1) / sizeof(size_t)) + 4;
		}
		else if (meta->cap != 0)
		{
			i += (meta->cap / sizeof(size_t)) + 3;
		}
		else
		{
			break;
		}
	}
	if (zone[steps - 1] != 0)
		return (total_bytes + print_zone((size_t *)zone[steps - 1], zone_size));
	return (total_bytes);
}

size_t	print_zone_lrg(size_t **zone)
{
	size_t		i;
	size_t		total_bytes;
	t_metalrg	*meta;

	i = 2;
	total_bytes = 0;
	while (i < BLK_SIZE / STEP - 1)
	{
		meta = (t_metalrg *)zone[i];
		if (meta && meta->meta.req)
		{
			printf("%p - %p : %lld bytes\n", meta + 1,
				(void *)meta + meta->meta.cap + sizeof(t_metalrg), meta->meta.cap);
		}
		i++;
	}
	if (zone[i])
		return (total_bytes + print_zone_lrg((size_t **)zone[i]));
	return (total_bytes);
}

void	show_alloc_mem(void)
{
	size_t bytes;
	
	printf("TINY : %p\n", map.tiny);
	bytes = print_zone(map.tiny, TINY_ZONE);
	printf("SMALL : %p\n", map.small);
	bytes += print_zone(map.small, SMALL_ZONE);
	printf("LARGE : %p\n", map.large);
	bytes += print_zone_lrg(map.large);
	printf("Total bytes : %lld\n", bytes);
}
