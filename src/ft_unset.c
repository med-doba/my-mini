/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:32:13 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/16 17:04:02 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_unset(t_lexer *lexer, t_env **env)
{
	t_env *head;
	t_env *tmp;

	head = *env;
	while(lexer->next)
	{
		while (*env)
		{
			if (ft_strcmp(lexer->next->content, (*env)->key) == 0)
			{
				free((*env)->key);
				free((*env)->value);
				tmp->next = (*env)->next;
				free(*env);
			}
			tmp = *env;
			*env = (*env)->next;
		}
		*env = head;
		lexer->next = lexer->next->next;
	}
	*env = head;
}
