/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:32:13 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/10 23:51:51 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_unset(t_lexer *lexer, t_env **env)
{
	t_env	*head;
	t_env	*tmp_prev;
	t_env	*tmp_next;
	t_env	*tmp;

	tmp_prev = NULL;
	tmp_next = NULL;
	head = *env;
	lexer = lexer->next;
	while (lexer)
	{
		while (*env)
		{
			tmp_next = (*env)->next;
			if (ft_strcmp(lexer->content, (*env)->name) == 0)
			{
				free((*env)->name);
				free((*env)->value);
				tmp = (*env)->next;
				free(*env);
			// }
				if (!tmp_prev)
				{
					printf("0\n");
					*env = tmp;
					head = *env;
					printf("env = %s\n", (*env)->name);
					// break;
				}
				else if (!tmp_next)
				{
					printf("1\n");
					*env = tmp_prev;
					(*env)->next = NULL;
					printf("env = %s\n", (*env)->name);
					// break;
				}
				else
				{
					printf("2\n");
					exit(1);
					*env = tmp_prev;
					(*env)->next = tmp;
					// break;
				}
			}
			tmp_prev = *env;
			*env = (*env)->next;
		}
		*env = head;
		lexer = lexer->next;
	}
	*env = head;
	gl.st = 0;
}
