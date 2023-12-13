
#include "../headers/libft.h"

/**
 * Calculates the number of elements in a linked list.
 *
 * @param lst  The linked list.
 * @return     The number of elements in the list.
 */
int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
