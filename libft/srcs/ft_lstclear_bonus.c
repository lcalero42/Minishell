/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:07:45 by lcalero           #+#    #+#             */
/*   Updated: 2024/11/19 10:23:35 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nxt;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		nxt = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = nxt;
	}
	free(*lst);
}
