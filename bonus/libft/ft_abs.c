
#include "../headers/libft.h"

/**
 * Calculates the absolute value of an integer.
 *
 * @param n The input integer whose absolute value needs to be calculated.
 * @return The absolute value of the input integer `n`.
 */
int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
