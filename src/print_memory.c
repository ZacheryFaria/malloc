/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:23:22 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/22 14:29:33 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>

int		print_zone(size_t *zone, size_t zone_size)
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
			printf("%p - %p : %d bytes\n", zone + i + 2, zone + i + 2 + (meta->cap / sizeof(size_t)), meta->req);
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

void	print_memory(void)
{
	int b = print_zone(map.small, SMALL_ZONE);
	printf("%d\n", b);
}
