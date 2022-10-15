/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:40:11 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/15 13:42:25 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	tmp = *lst;
	while ((*lst)->next != NULL)
	{
		*lst = (*lst)->next;
	}
	(*lst)->next = new;
	new->next = NULL;
	*lst = tmp;
}

t_lexer	*ft_lstnew(char *content, int linked)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (node == NULL)
		return (NULL);
	node->content = ft_strdup(content);
	node->next = NULL;
	node->linked = linked;
	return (node);
}

void	ft_free_lst(t_lexer **head)
{
	t_lexer		*tmp;

	while ((*head))
	{
		free((*head)->content);
		tmp = (*head)->next;
		free((*head));
		(*head) = tmp;
	}
}

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**convert_list(t_env *env)
{
	char	**envv;
	int		i;

	i = 0;
	envv = (char **)malloc((ft_lstsize(env) + 1) * sizeof(char *));
	if (envv == NULL)
		return (NULL);
	while (env)
	{
		envv[i] = ft_strjoin2(env->name, "=");
		if (!envv[i])
			return (freeall(&envv[i], i - 1));
		envv[i] = ft_strjoin(envv[i], env->value);
		if (!envv[i])
			return (freeall(&envv[i], i - 1));
		env = env->next;
		i++;
	}
	envv[i] = NULL;
	return (envv);
}
