/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmalloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 10:35:43 by zfaria            #+#    #+#             */
/*   Updated: 2020/01/18 14:46:01 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMALLOC_H
# define LIBMALLOC_H

# include <stdlib.h>

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
void	*calloc(size_t num, size_t size);

#endif
