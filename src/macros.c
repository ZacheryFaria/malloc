/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 12:55:03 by zfaria            #+#    #+#             */
/*   Updated: 2020/01/19 12:59:41 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libmalloc_util.h>

size_t	steps(size_t size)
{
	return (size / 8);
}

size_t	align(size_t size)
{
	return (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1));
}

size_t	align_large(size_t size)
{
	return (((size) + (BLK_SIZE - 1)) & ~(BLK_SIZE - 1));
}

int		is_free(t_meta *meta)
{
	return (!(meta->cap & 1));
}
