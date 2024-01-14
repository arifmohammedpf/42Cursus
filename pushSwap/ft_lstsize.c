
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		  count;
	t_list	*node;

	count = 0;
	node = lst;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}