/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:26:00 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/03 17:28:28 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void			handle_file(t_env *env, char *str)
{
	env->files[env->has_file] = ft_strdup(str);
	env->has_file++;
}

void			handle_flags(t_env *env, int argc, char **argv)
{
	int i;

	while (1 + env->flag_count < argc && (i = -1))
	{
		if (argv[1 + env->flag_count][++i] == '-')
			while (argv[1 + env->flag_count][++i])
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
			}
		else
			break ;
		env->flag_count++;
	}
}

static void		call(t_env *env, int i)
{
	if (env->R_flag)
		recurse_folders(env, env->head[i]);
	if (!env->t_flag)
		sort_list(env, env->head[i], &sort_by_alpha);
	if (env->t_flag)
		sort_list(env, env->head[i], &sort_by_time);
	if (env->has_file)
		ft_printf("\n\n");
	print_list(env, env->head[i]);
}

static void		get_calls(t_env *env)
{
	int i;

	env->t_flag ? sort_list_array(env, &sort_by_time)
	: sort_list_array(env, &sort_by_alpha);
	env->t_flag ? sort_str_array(env, &str_sort_by_time)
	: sort_str_array(env, &str_sort_by_alpha);
	print_file(env);
	i = -1;
	while (++i < env->index)
	{
		call(env, i);
		if (i + 1 < env->index)
			ft_printf("\n\n");
	}
}

void			handle_args(t_env *env, int argc, char **args)
{
	int i;

	env->arg_count = argc - 1 - env->flag_count;
	if (!env->arg_count)
	{
		env->head[env->index] = ft_lstnew(NULL, 0);
		env->head[env->index]->next = NULL;
		add_directory_to_list(env, ".", env->head[env->index]);
		env->index++;
	}
	else if (env->arg_count >= 1 && (i = -1))
	{
		while (++i < env->arg_count)
			if (is_file(args[i + 1 + env->flag_count]))
				handle_file(env, args[i + 1 + env->flag_count]);
			else
			{
				env->head[env->index] = ft_lstnew(NULL, 0);
				env->head[env->index]->next = NULL;
				add_directory_to_list(env, args[i + 1 + env->flag_count],
					env->head[env->index]);
				env->index++;
			}
	}
	get_calls(env);
}
