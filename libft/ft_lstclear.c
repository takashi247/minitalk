#include "libft.h"

void
	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*tmp;

	if (lst && (*del))
	{
		current = *lst;
		while (current)
		{
			tmp = current->next;
			ft_lstdelone(current, del);
			current = tmp;
		}
		*lst = NULL;
	}
}
