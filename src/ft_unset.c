/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:32:13 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/17 17:09:53 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_unset_(t_env **env, t_env **tmp_prev, t_env **tmp_next, t_env **head)
{
	free((*env)->name);
	free((*env)->value);
	free(*env);
	if (!(*tmp_prev))
		*head = *tmp_next;
	else if (!(*tmp_next))
		(*tmp_prev)->next = NULL;
	else
		(*tmp_prev)->next = *tmp_next;
}

int	ft_ft_test(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] >= '0' && str[0] <= '9')
			return (1);
		if (ft_if_condition(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_lexer *lexer, t_env **env, t_env	*tmp_prev, t_env *tmp_next)
{
	t_env	*head;

	head = *env;
	while (lexer)
	{
		tmp_prev = NULL;
		tmp_next = NULL;
		while (*env)
		{
			tmp_next = (*env)->next;
			if (ft_strcmp(lexer->content, (*env)->name) == 0)
			{
				ft_unset_(env, &tmp_prev, &tmp_next, &head);
				break ;
			}
			tmp_prev = *env;
			*env = (*env)->next;
		}
		if (ft_ft_test(lexer->content) == 1)
			ft_putstr_fd("not a valid identifier\n", 2);
		*env = head;
		lexer = lexer->next;
	}
}
