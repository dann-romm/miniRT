#include <stdlib.h>
#include "utils_ft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*dst;

	if (!ptr)
		return (malloc(size));
	if (!size)
		return (ptr);
	dst = malloc(size);
	ft_memcpy(dst, ptr, size);
	return (dst);
}
