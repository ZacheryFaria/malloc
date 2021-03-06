/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:23:22 by zfaria            #+#    #+#             */
/*   Updated: 2020/01/18 14:45:37 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <libft.h>

size_t	print_zone(size_t *zone, size_t zsize)
{
	size_t	i;
	size_t	bytes;
	t_meta	*meta;

	i = 2;
	bytes = 0;
	while (i < zsize / STEP - 1)
	{
		meta = (t_meta *)(zone + i);
		if (!ISFREE(meta))
		{
			ft_printf("%p - %p : %lld bytes\n", zone + i + 2, zone + i + 2 +
				(meta->cap / sizeof(size_t)), meta->req);
			bytes += meta->req;
			i += ((meta->cap - 1) / sizeof(size_t)) + 4;
		}
		else if (meta->cap != 0)
			i += (meta->cap / sizeof(size_t)) + 3;
		else
			break ;
	}
	if (zone[zsize / STEP - 1] != 0)
		return (bytes + print_zone((size_t *)zone[zsize / STEP - 1], zsize));
	return (bytes);
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
			ft_printf("%p - %p : %lld bytes\n", meta + 1, (void *)meta +
				meta->meta.cap + sizeof(t_metalrg), meta->meta.cap);
			total_bytes += meta->meta.req;
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

	ft_printf("TINY : %p\n", g_map.tiny);
	bytes = print_zone(g_map.tiny, TINY_ZONE);
	ft_printf("SMALL : %p\n", g_map.small);
	bytes += print_zone(g_map.small, SMALL_ZONE);
	ft_printf("LARGE : %p\n", g_map.large);
	bytes += print_zone_lrg(g_map.large);
	ft_printf("Total bytes : %lld\n", bytes);
}
