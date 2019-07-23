/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:43:53 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/23 14:55:21 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <sys/mman.h>
#include <stdio.h>
#include <signal.h>

void	free_large(size_t *ptr)
{
	t_metalrg	*meta;
	int			res;

	meta = (t_metalrg *)ptr;
	*meta->back = 0;
	printf("%lld\n", meta->meta.cap);
	res = munmap(ptr, meta->meta.cap);
	if (res == -1)
		perror("malloc");
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
	size_t	*zsize;
	if (!ptr)
		return ;

	zone = find_zone_large(ptr);
	if (zone)
		free_large(zone);
	else
	{	
		zone = find_zone(ptr, &zsize);
		if (!valid_pointer(ptr, zone, zsize))
		{
			printf("malloc: pointer %p being freed was not allocated.\n", ptr);
			raise(SIGABRT);
		}
		free_internal(ptr);
	}
}
