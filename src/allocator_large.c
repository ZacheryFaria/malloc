/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator_large.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 12:40:40 by zfaria            #+#    #+#             */
/*   Updated: 2020/01/19 12:41:10 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <libft.h>

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
	size_t		bytes;
	size_t		*ptr;
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
