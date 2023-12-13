
#include "../headers/libft.h"

/**
 * Creates a new list element with the specified content.
 *
 * @param content  The content of the new element.
 * @return         The new list element, or NULL if an error occurred.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = 0;
	return (new);
}
