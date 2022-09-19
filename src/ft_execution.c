/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:00:17 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/19 15:25:23 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_collect_cmd(t_lexer **lexer, t_env **env)
{
	// int		pipe;
	// t_lexer	*top;
	// char	*ptr;

	// pipe = 0;
	// top = *lexer;
	// ptr = ft_strdup("");
	// while(top)
	// {
	// 	if(top->ch != '|')
	// 		pipe++;
	// 	ptr = ft_strjoin(ptr, top->content);
	// 	ptr = ft_strjoin(ptr, " ");
	// 	top = top->next;
	// }
	// (void)env;
	ft_built_in_uppercase(*lexer, *env);
	ft_built_in_lowercase(*lexer, *env);
}
