
#include "../headers/libft.h"

/**
 * Iterates over a linked list and applies a function to each element.
 *
 * @param lst The linked list to iterate over.
 * @param f The function to apply to each element.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
