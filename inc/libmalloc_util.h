/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmalloc_util.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 10:35:24 by zfaria            #+#    #+#             */
/*   Updated: 2019/07/30 10:55:13 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMALLOC_UTIL_H
# define LIBMALLOC_UTIL_H

# include <libmalloc.h>

# define BLK_SIZE 4096

# define TINY_CAP 256
# define SMALL_CAP 1024

# define TINY_ZONE (BLK_SIZE * 8)
# define SMALL_ZONE (BLK_SIZE * 32)

# define ZONE_CAP 64

# define STEP sizeof(size_t)

# define ALIGNMENT 8
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

# define ALIGN_LARGE(size) (((size) + (BLK_SIZE - 1)) & ~(BLK_SIZE - 1))

# define ISFREE(meta) (!(meta->cap & 1))

typedef struct	s_meta {
	size_t		cap;
	size_t		req;
}				t_meta;

typedef struct	s_metalrg {
	t_meta		meta;
	size_t		**back;
}				t_metalrg;

typedef	struct	s_map {
	size_t		*tiny;
	size_t		*small;
	size_t		**large;
}				t_map;

extern	t_map	map;
extern	int		g_malloc_opts;

void			init_map(void);

void			*alloc(size_t size);

void			*find_free_mem(size_t *zone, size_t zsize, size_t req);
void			*alloc_large(size_t req);

size_t			*find_zone(size_t *ptr, size_t *zsize);
size_t			*find_zone_large(size_t *ptr);

int				valid_pointer(size_t *ptr, size_t *zone, size_t zsize);



#endif
