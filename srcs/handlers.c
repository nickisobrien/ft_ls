/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:26:00 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/01 17:59:15 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	handle_flags(t_env *env, int argc, char **argv)
{
	int i;

	if (argc == 1)
		return ;
	while (1 + env->flag_count < argc)
	{
		i = 0;
		if (argv[1 + env->flag_count][i++] == '-')
		{
			while (argv[1 + env->flag_count][i])
			{
				if (argv[1 + env->flag_count][i] == 'l')
					env->l_flag = 1;
				else if (argv[1 + env->flag_count][i] == 'r')
					env->r_flag = 1;
				else if (argv[1 + env->flag_count][i] == 't')
					env->t_flag = 1;
				else if (argv[1 + env->flag_count][i] == 'a')
					env->a_flag = 1;
				else if (argv[1 + env->flag_count][i] == 'R')
					env->R_flag = 1;
				else
					usage();
				i++;
			}
		}
		else
			break ;
		env->flag_count++;
	}
}

void	call(t_env *env, int i)
{
	if (env->R_flag)
		recurse_folders(env, env->head[i]);
	if (!env->t_flag)
		sort_list(env, env->head[i], &sort_by_alpha);
	if (env->t_flag)
		sort_list(env, env->head[i], &sort_by_time);
	print_list(env, env->head[i]);
}

void	handle_args(t_env *env, int argc, char **args)
{
	int i;

	i = -1;
	env->arg_count = argc - 1 - env->flag_count;
	malloc_llarr(env);
	if (!env->arg_count)
	{
		env->head[env->index] = ft_lstnew(NULL, 0);
		env->head[env->index]->next = NULL;
		add_directory_to_list(env, ".", env->head[env->index]);
		env->index++;
	}
	else if (env->arg_count >= 1)
	{
		while (++i < env->arg_count)
		{
			env->head[env->index] = ft_lstnew(NULL, 0);
			env->head[env->index]->next = NULL;
			add_directory_to_list(env, args[i + 1 + env->flag_count], env->head[env->index]);
			env->index++;
		}
	}
	env->t_flag ? sort_array(env, &sort_by_time) : sort_array(env, &sort_by_alpha);
	i = -1;
	while (++i < env->index)
	{
		call(env, i);
		if (i + 1 < env->index)
			ft_printf("\n\n");
	}
}