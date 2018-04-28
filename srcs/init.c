/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:13:50 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/27 18:14:44 by nobrien          ###   ########.fr       */
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
	env->head = ft_lstnew(NULL, 0);
	env->head->next = NULL;
}

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

void	handle_args(t_env *env, int argc, char **args)
{
	int i;

	i = -1;
	env->arg_count = argc - 1 - env->flag_count;
	if (!env->arg_count)
		add_directory_to_list(env, ".", env->head);
	else if (env->arg_count >= 1)
		while (++i < env->arg_count)
			add_directory_to_list(env, args[i + 1 + env->flag_count], env->head);
	if (env->R_flag)
		recurse_folders(env, env->head);
	if (!env->t_flag)
		sort_list(env, env->head, &sort_by_alpha);
	if (env->t_flag)
		sort_list(env, env->head, &sort_by_time);
	if (env->r_flag)
		sort_list(env, env->head, &sort_by_revalpha);//need to switch to reverse
	print_list(env, env->head);
}
