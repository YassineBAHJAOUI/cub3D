
#include "../headers/libft.h"

/**
 * Clears a linked list by deleting all its elements.
 *
 * @param lst The address of a pointer to the first element of the list.
 * @param del The function used to delete the content of an element.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
