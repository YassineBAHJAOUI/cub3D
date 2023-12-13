
#include "../headers/libft.h"

/**
 * Copy memory block.
 *
 * This function copies a specified number of bytes from the source memory
 * block (src) to the destination memory block (dest). It returns a pointer
 * to the destination memory block.
 *
 * @param dest A pointer to the destination memory block where the copied
 * bytes will be placed.
 * @param src A pointer to the source memory block from where the bytes will
 * be copied.
 * @param n The number of bytes to be copied.
 * @return A pointer to the destination memory block (dest).
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
