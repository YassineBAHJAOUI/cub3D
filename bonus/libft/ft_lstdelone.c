
#include "../headers/libft.h"

/**
 * Deletes a single element from a linked list.
 *
 * @param lst The element to delete.
 * @param del The function used to delete the content of the element.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
