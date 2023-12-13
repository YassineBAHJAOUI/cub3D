
#include "../headers/libft.h"

/**
 * Calculate the number of digits in a given number.
 *
 * @param nbr The number for which the length is to be calculated.
 *
 * @return The number of digits in the given number.
 */
int	ft_nbrlen(long long nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}
