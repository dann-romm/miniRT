#ifndef UTILS_FT_H
# define UTILS_FT_H

# include <stdlib.h>

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t size);

void	*ft_realloc(void *ptr, size_t size);

void	*ft_memset(void *b, int c, size_t len);

void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
