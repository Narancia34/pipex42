/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:46:01 by mgamraou          #+#    #+#             */
/*   Updated: 2024/11/06 16:41:28 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lstptr;

	if (!lst || !f)
		return ;
	lstptr = lst;
	while (lstptr != NULL)
	{
		f(lstptr->content);
		lstptr = lstptr->next;
	}
}
