
#include "../headers/libft.h"

/**
 * Copy a string into a destination buffer with a size limit.
 *
 * @param dest The destination buffer to which the source string will be
 *             copied.
 * @param src  The source string to be copied.
 * @param size The size of the destination buffer.
 *
 * @return The total length of the source string (excluding the
 *         null-terminator), regardless of the given size limit. Note that the
 *         destination buffer is modified.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	a;

	i = 0;
	a = ft_strlen((char *)src);
	if (size == 0)
		return (a);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (a);
}
