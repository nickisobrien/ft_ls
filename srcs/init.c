/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:13:50 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/01 17:53:13 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	init_env(t_env *env)
{
	env->l_flag = 0;
	env->R_flag = 0;
	env->a_flag = 0;
	env->t_flag = 0;
	env->r_flag = 0;
	env->flag_count = 0;
	env->index = 0;
}

void	malloc_llarr(t_env *env)
{
	if (env->arg_count)
	{
		if (!(env->head = (malloc(sizeof(t_list *) * env->arg_count))))
			error("Malloc error");
	}
	else
		if (!(env->head = (malloc(sizeof(t_list *) * 1))))
			error("Malloc error");
}
