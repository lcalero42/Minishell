/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis <luis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:19:35 by luis              #+#    #+#             */
/*   Updated: 2025/03/17 16:22:10 by luis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_redirection *redir)
{
	t_redirection *tmp;
	t_redirection *next;
	
	tmp = redir;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->file)
			free(tmp->file);
		tmp = next;
	}
}
