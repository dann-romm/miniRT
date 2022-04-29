#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	i = -1;
	while (++i < n)
		((char *) dst)[i] = ((char *) src)[i];
	while (i < n)
		((char *) dst)[i++] = 0;
	return (dst);
}
