/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmalloc_util.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 10:35:24 by zfaria            #+#    #+#             */
/*   Updated: 2020/01/19 12:59:13 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMALLOC_UTIL_H
# define LIBMALLOC_UTIL_H

# include <libmalloc.h>
# include <pthread.h>

# define BLK_SIZE 4096

# define TINY_CAP 256
# define SMALL_CAP 1024

# define TINY_ZONE 32768
# define SMALL_ZONE 131072

# define ZONE_CAP 64

# define STEP 8

# define ALIGNMENT 8

# define STEPS steps

# define ALIGN align

# define ALIGN_LARGE align_large

# define ISFREE is_free

typedef pthread_mutex_t	t_mutex;

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

extern	t_map	g_map;
extern	t_mutex g_lock;
extern	int		g_malloc_opts;

void			init_map(void);

void			*alloc(size_t size);

void			*find_free_mem(size_t *zone, size_t zsize, size_t req);
void			*alloc_large(size_t req);

size_t			*find_zone(size_t *ptr, size_t *zsize);
size_t			*find_zone_large(size_t *ptr);

int				valid_pointer(size_t *ptr, size_t *zone, size_t zsize);

int				is_free(t_meta *meta);

size_t			steps(size_t size);

size_t			align(size_t size);

size_t			align_large(size_t size);

#endif
