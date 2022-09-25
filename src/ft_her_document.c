/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_her_document.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:16:53 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/25 18:17:23 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_expand_herdoc(t_lexer **lexer)
{
	if ((*lexer) && !ft_strcmp((*lexer)->content, "<<") && (*lexer)->next)
	{
		(*lexer) = (*lexer)->next;
		if ((*lexer)->next)
			(*lexer) = (*lexer)->next;
		else if (!(*lexer)->next)
			return (1);
	}
	return (0);
}
