
#include "../headers/libft.h"

/**
 * Fill a block of memory with a particular value.
 *
 * @param str Pointer to the memory block to be filled.
 * @param c   Value to be set (converted to an unsigned char).
 * @param n   Number of bytes to be set.
 *
 * @return Pointer to the memory block (str).
 */
void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)str)[i] = c;
		i++;
	}
	return (str);
}
