/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:56:20 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/25 16:10:32 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_env(t_env *env)
{
	t_env	*top;

	top = env;
	while (top)
	{
		if (top->name && top->value)
			printf("%s=%s\n", top->name, top->value);
		top = top->next;
	}
	gl.st = 0;
}
