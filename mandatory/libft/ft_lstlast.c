
#include "../headers/libft.h"

/**
 * Returns a pointer to the last element of a linked list.
 *
 * @param lst The linked list.
 * @return A pointer to the last element, or NULL if the list is empty.
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
