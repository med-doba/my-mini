/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <amasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:32:13 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/09 10:57:12 by amasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_unset(t_lexer *lexer, t_env **env)
{
	t_env	*head;
	t_env	*tmp;

	head = *env;
	while (lexer->next)
	{
		while (*env)
		{
			if (ft_strcmp(lexer->next->content, (*env)->name) == 0)
			{
				free((*env)->name);
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
	gl.st = 0;
}
