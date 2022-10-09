/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amasnaou <amasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:56:20 by med-doba          #+#    #+#             */
/*   Updated: 2022/10/09 10:56:22 by amasnaou         ###   ########.fr       */
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
