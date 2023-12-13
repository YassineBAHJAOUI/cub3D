
#include "../headers/libft.h"

/**
 * Formats and prints a single character with padding.
 *
 * @param values    Pointer to the buffer structure.
 * @param c         The character to be printed.
 * @return          The number of characters printed.
 */
int	ft_format_putchar(t_buffer *values, char c)
{
	int	count;

	count = 0;
	if (values->minus == 1)
	{
		count += write(1, &c, 1);
		while (values->width > 1)
		{
			count += write(1, " ", 1);
			values->width--;
		}
	}
	else
	{
		while (values->width > 1)
		{
			count += write(1, " ", 1);
			values->width--;
		}
		count += write(1, &c, 1);
	}
	return (count);
}
