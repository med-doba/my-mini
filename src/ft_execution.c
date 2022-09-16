/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:00:17 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/14 12:59:48 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_collect_cmd(t_lexer **lexer)
{
	// char	**tab;
	int	pipe;
	t_lexer	*top;
	char	*ptr;

	top = *lexer;
	pipe = 0;
	ptr = ft_strdup("");
	while(top)
	{
		if(ft_strcmp(top->content, "|") == 0 && top->ch != '"' && top->ch != '\'')
			pipe++;
		ptr = ft_strjoin(ptr, top->content);
		ptr = ft_strjoin(ptr, " ");
		top = top->next;
	}
	// printf("ptr == %s---->>%d\n", ptr, pipe);
}
