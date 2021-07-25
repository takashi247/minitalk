#include "libft.h"

int
	ft_lstsize(t_list *lst)
{
	int	len_lst;

	if (!lst)
		return (0);
	len_lst = 0;
	while (lst)
	{
		len_lst++;
		lst = lst->next;
	}
	return (len_lst);
}
