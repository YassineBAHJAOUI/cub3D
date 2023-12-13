
#include "../headers/libft.h"

/**
 * Prints a positive number with width formatting.
 *
 * @param number     The number to be printed.
 * @param values     The buffer structure containing formatting information.
 * @param len        The length of the number.
 * @return The total number of characters printed.
 */
int	ft_print_posnbrw2(char *number, t_buffer *values, int len)
{
	int	count;

	count = 0;
	while ((values->width--) > len)
		count += write(1, " ", 1);
	while ((values->precision--) > (int)ft_strlen(number))
		count += write(1, "0", 1);
	return (count);
}
