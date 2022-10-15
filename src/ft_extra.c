/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:59:01 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/16 00:01:58 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_nbr_of_pipes(t_lexer *lexer)
{
	int		pipe;
	t_lexer	*top;

	pipe = 0;
	top = lexer;
	while (top)
	{
		if (top->ch == '|')
			pipe++;
		top = top->next;
	}
	return (pipe);
}

int	ft_run_redirection(t_lexer *lexer, t_env *env)
{
	char	*file;
	int		rtn;
	t_env	*env_her_doc;

	env_her_doc = env;
	file = lexer->next->content;
	rtn = 0;
	if (ft_strcmp(lexer->content, ">") == 0)
		rtn = ft_r_output(file);
	else if (ft_strcmp(lexer->content, ">>") == 0)
		rtn = ft_append(file);
	else if (ft_strcmp(lexer->content, "<") == 0)
		rtn = ft_r_input(file);
	else if (ft_strcmp(lexer->content, "<<") == 0)
		rtn = ft_her_duc(file, env_her_doc);
	if (rtn == -1)
		return (-1);
	return (0);
}
