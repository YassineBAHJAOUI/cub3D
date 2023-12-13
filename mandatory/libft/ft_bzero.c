
#include "../headers/libft.h"

/**
 * Fills a block of memory with zeroes.
 *
 * @param str Pointer to the start of the memory block.
 * @param n   Number of bytes to zero out.
 */
void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}
