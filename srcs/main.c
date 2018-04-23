/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 10:42:10 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/23 02:00:43 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	recurse_folders(t_env *env);

void	error(char *err)
{
	ft_printf("Error: %s\n", err);
	exit(-1);
}

DIR		*open_dir(char *directory)
{
	DIR *dir;

	dir = opendir(directory);
	if (dir == NULL)
		return (NULL);
		// error("Unable to open directory.");
	return (dir);
}

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

void	close_dir(DIR *dir)
{
	closedir(dir);
}

char	*join_paths(char *path_a, char *path_b)
{
	return (ft_strjoin(ft_strjoin(path_a, "/"), path_b));//leak?
}

void	print_l_info(void)
{
	ft_printf("info%-20c", ' ');
}

void	print_directory_name(char *str)
{
	ft_printf("%s:\n", str);
}

t_list		*new_list_item(void)
{
	t_list *tmp;

	tmp = malloc(sizeof(t_list));
	tmp->next = NULL;
	tmp->content = NULL;
	tmp->content_size = 0;
	return (tmp);
}

void	list_swap(t_list *a, t_list *b)
{
	(void)a;
	(void)b;
	t_list	tmp;
	
	tmp.content = ft_strdup(a->content);
	tmp.directory = ft_strdup(a->directory);
	tmp.content_size = a->content_size;
	a->content = b->content;
	a->directory = b->directory;
	a->content_size = b->content_size;
	b->content = tmp.content;
	b->directory = tmp.directory;
	b->content_size = tmp.content_size;
}

void	sort_list(t_env *env, int (*cmp)(t_list *, t_list *))
{
	t_list		*iter;
	int			unsorted;

	unsorted = 1;
	while (unsorted)
	{
		unsorted = 0;
		iter = env->head;
		while (iter->next->next)
		{
			if ((*cmp)(iter, iter->next))
			{
				unsorted = 1;
				list_swap(iter, iter->next);
			}
			iter = iter->next;
		}
	}
}

int		sort_by_alpha(t_list *a, t_list *b)
{
	(void)a;
	(void)b;
	if ((ft_strcmp(a->content, b->content)) > 0)
		return (1);
	return (0);
}

void	print_list(t_env *env)
{
	t_list *iter;

	iter = env->head;
	while (iter->next)
	{
		if (iter->content[0] != '.' || env->a_flag)
			ft_printf("%-10s", iter->content);
		iter = iter->next;
	}
	ft_printf("\n");
}

void	add_directory_to_list(t_env *env, char *directory)
{
	struct dirent	*sd;
	DIR				*dir;
	t_list			*iter;

	iter = env->head;
	if (!(dir = open_dir(directory)))
		return ;
	while (iter->next)
		iter = iter->next;
	while ((sd = readdir(dir)) != NULL)
	{
		iter->directory = ft_strdup(directory);
		iter->content = ft_strdup(sd->d_name);
		iter->content_size = ft_strlen(sd->d_name);
		iter->next = new_list_item();
		iter = iter->next;
	}
	close_dir(dir);
}

void	recurse_folders(t_env *env)
{
	t_list *iter;
	struct stat buf;

	iter = env->head;
	while (iter->next)
	{
		stat(iter->content, &buf);
		if (S_ISDIR(buf.st_mode) && !ft_strequ(iter->content, "..") && !ft_strequ(iter->content, ".") && !ft_strequ(iter->content, "libft.a") && iter->content[0] != '.')
		{
			add_directory_to_list(env, join_paths(iter->directory, iter->content));
		}
		iter = iter->next;
	}
}

void	print_recursed_directory(t_env *env)
{
	t_list *iter;

	iter = env->head;
	while (iter->next)
	{
		if (iter->content[0] != '.')
		ft_printf("%-16s  ", iter->content);
		if (iter->next->directory && !ft_strequ(iter->directory, iter->next->directory))
			ft_printf("\n\n%s:\n", iter->next->directory);
		iter = iter->next;
	}
}

void	handle_flags(t_env *env, int argc, char **argv)
{
	char *str;

	if (argc == 1)
		return ;
	if ((str = ft_strchr(argv[1 + env->flag_count], '-')) != NULL)//can be while loop?
	{
		env->l_flag = (*(str + 1) == 'l' ? 1 : 0);
		env->R_flag = (*(str + 1) == 'R' ? 1 : 0);
		env->a_flag = (*(str + 1) == 'a' ? 1 : 0);
		env->t_flag = (*(str + 1) == 't' ? 1 : 0);
		env->r_flag = (*(str + 1) == 'r' ? 1 : 0);
		env->flag_count++;
	}
}

void	handle_args(t_env *env, int argc, char **args)
{
	int i;

	i = env->flag_count;
	if (argc - i == 1)
		add_directory_to_list(env, ".");
	else if (argc - i >= 2)
		while (++i < argc)
			add_directory_to_list(env, args[i]);
	if (env->R_flag)
	{
		recurse_folders(env);
		print_recursed_directory(env);
	}
	else
	{
		if (env->t_flag)
			sort_list(env, &sort_by_alpha);
		print_list(env);
	}
}

int		main(int argc, char **argv)
{
	t_env env;

	init_env(&env);
	handle_flags(&env, argc, argv);
	handle_args(&env, argc, argv);

	return (0);
}
