
#include "../headers/libft.h"

/**
 * Allocates and initializes a block of memory with zeroes.
 *
 * @param nmemb Number of elements to allocate.
 * @param size  Size of each element.
 * @return      Pointer to the allocated memory block, or NULL if
 * allocation fails.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	dest = malloc(nmemb * size);
	if (!dest)
		return (0);
	ft_bzero(dest, (nmemb * size));
	return (dest);
}
