#ifndef FT_UTILS_H
# define FT_UTILS_H

# include <stdlib.h>

// utils/ft_calloc.c
void	*ft_calloc(size_t count, size_t size);

// utils/ft_bzero.c
void	ft_bzero(void *s, size_t n);

// utils/ft_memset.c
void	*ft_memset(void *b, int c, size_t len);

// utils/ft_memcpy.c
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
