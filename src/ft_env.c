/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:56:20 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/19 16:31:11 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_env(t_env *env)
{
	t_env	*top;

	top = env;
	while(top)
	{
		if (top->key && top->value)
			printf("%s=%s\n", top->key, top->value);
		top = top->next;
	}
}
