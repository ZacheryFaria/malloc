/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:58:30 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/31 11:26:03 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>
#include <libft.h>

void	*calloc(size_t num, size_t size)
{
	void *ptr;

	ptr = malloc(num * size);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, num * size);
	return (ptr);
}
