/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:32:13 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/11 01:03:55 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_unset(t_lexer *lexer, t_env **env)
{
	t_env	*head;
	t_env	*tmp_prev;
	t_env	*tmp_next;
 
	head = *env;
	lexer = lexer->next;
	while (lexer)
	{
		tmp_prev = NULL;
		tmp_next = NULL;
		while (*env)
		{
			tmp_next = (*env)->next;
			if (ft_strcmp(lexer->content, (*env)->name) == 0)
			{
				free((*env)->name);
				free((*env)->value);
				free(*env);
				if (!tmp_prev)
					head = tmp_next;
				else if (!tmp_next)
					tmp_prev->next = NULL;
				else
					tmp_prev->next = tmp_next;
				break ;
			}
			tmp_prev = *env;
			*env = (*env)->next;
		}
		*env = head;
		lexer = lexer->next;
	}
	gl.st = 0;
}
