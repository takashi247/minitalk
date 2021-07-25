#include "libft.h"

void
	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = *lst;
			*lst = new;
			new->next = tmp;
		}
	}
}
