
#include "../headers/libft.h"

/**
 * Calculates the length (number of digits) of an unsigned long long integer
 * in the specified base.
 *
 * @param n     The unsigned long long integer for which to calculate
 * the length.
 * @param base  The base to use for the calculation (e.g., 10 for decimal).
 * @return      The length of the integer in the specified base.
 */
int	ft_getlength(unsigned long long n, int base)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		length++;
		n /= base;
	}
	return (length);
}
