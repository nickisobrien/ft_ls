/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 10:42:10 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/25 21:28:51 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	recurse_folders(t_env *env, t_list *head);

void	error(char *err)
{
	ft_printf("Error: %s\n", err);
	exit(-1);
}

void	usage(void)
{
	ft_printf("usage: ls [-alrRt] [file ...]");
	exit(-1);
}

DIR		*open_dir(char *directory)
{
	DIR *dir;

	dir = opendir(directory);
	if (dir == NULL)
		return (NULL);
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
	char	*tmp;

	tmp = path_a;
	path_a = ft_strjoin(path_a, "/");
	// ft_strdel(&tmp); leaks?

	tmp = path_a;
	path_a = ft_strjoin(path_a, path_b);
	ft_strdel(&tmp);
	return (path_a);
}

void	print_permissions(struct stat abuf)
{
	ft_printf( (S_ISDIR(abuf.st_mode)) ? "d" : "-");
    ft_printf( (abuf.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf( (abuf.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf( (abuf.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf( (abuf.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf( (abuf.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf( (abuf.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf( (abuf.st_mode & S_IROTH) ? "r" : "-");
    ft_printf( (abuf.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf( (abuf.st_mode & S_IXOTH) ? "x" : "-");
}

void	print_l_info(t_list *item)
{
	struct stat		abuf;
	char			*t;

	stat(join_paths(item->directory, item->content), &abuf);
	print_permissions(abuf);
	ft_printf(" %2d", abuf.st_nlink);
	ft_printf(" %s ", getpwuid(abuf.st_uid)->pw_name);
	ft_printf(" %s ", getgrgid(abuf.st_gid)->gr_name);
	ft_printf(" %5d", abuf.st_size);
	t = ctime(&(abuf.st_mtime)) + 4;
	ft_printf(" %.12s ", t);
}

t_list		*new_list_item(void)
{
	t_list *tmp;

	tmp = malloc(sizeof(t_list));
	tmp->next = NULL;
	tmp->content = NULL;
	tmp->content_size = 0;
	tmp->down = NULL;
	return (tmp);
}

void	list_swap(t_list *a, t_list *b)//change where next is pointing instead of swapping content
{
	t_list	tmp;
	
	tmp.content = a->content;
	tmp.directory = a->directory;
	tmp.content_size = a->content_size;
	tmp.down = a->down;
	a->content = b->content;
	a->directory = b->directory;
	a->content_size = b->content_size;
	a->down = b->down;
	b->content = tmp.content;
	b->directory = tmp.directory;
	b->content_size = tmp.content_size;
	b->down = tmp.down;
}

void	sort_list(t_env *env, t_list *base, int (*cmp)(t_list *, t_list *))
{
	t_list		*iter;
	int			unsorted;

	unsorted = 1;
	while (unsorted)
	{
		unsorted = 0;
		iter = base;
		while (iter->next && iter->next->next)
		{
			if ((*cmp)(iter, iter->next))
			{
				unsorted = 1;
				list_swap(iter, iter->next);
			}
			iter = iter->next;
		}
	}

	iter = base;
	while (iter->next)
	{
		if (iter->down)
			sort_list(env, iter->down, cmp);
		iter = iter->next;
	}
}

int		sort_by_alpha(t_list *a, t_list *b)
{
	return ((ft_strcmp(a->content, b->content)) > 0);
}

int		sort_by_revalpha(t_list *a, t_list *b)
{
	return (!((ft_strcmp(a->content, b->content)) > 0));
}

int		sort_by_time(t_list *a, t_list *b)
{
	struct stat		abuf;
	struct stat		bbuf;

	stat(join_paths(a->directory, a->content), &abuf);
	stat(join_paths(b->directory, b->content), &bbuf);
	return (abuf.st_mtimespec.tv_sec < bbuf.st_mtimespec.tv_sec ||
		(abuf.st_mtimespec.tv_sec == bbuf.st_mtimespec.tv_sec &&
			abuf.st_mtimespec.tv_nsec < bbuf.st_mtimespec.tv_nsec));
}

void	print_list(t_env *env, t_list *base)
{
	t_list *iter;

	iter = base;
	while (iter->next)
	{
		if (env->l_flag)
			print_l_info(iter);
		ft_printf("%-10s ", iter->content);
		if (env->l_flag)
			ft_printf("\n");
		iter = iter->next;
	}
	ft_printf("\n");
	iter = base;
	while (iter->next)
	{
		if (iter->down)
		{
			(env->l_flag) ? ft_printf("%s/%s:\n", iter->directory, iter->content) : ft_printf("\n%s/%s:\n", iter->directory, iter->content);
			print_list(env, iter->down);
		}
		iter = iter->next;
	}
}

void	add_directory_to_list(t_env *env, char *directory, t_list *base)
{
	struct dirent	*sd;
	DIR				*dir;
	t_list			*iter;

	if (!(dir = open_dir(directory)))
		return ;
	if (base->content)
	{
		base->down = new_list_item();
		iter = base->down;
	}
	else
		iter = base;
	while ((sd = readdir(dir)) != NULL)
	{
		if (sd->d_name[0] == '.' && !(env->a_flag))
			continue ;
		iter->directory = ft_strdup(directory);
		iter->content = ft_strdup(sd->d_name);
		iter->content_size = ft_strlen(sd->d_name);
		iter->next = new_list_item();
		iter = iter->next;
	}
	close_dir(dir);
}

void	recurse_folders(t_env *env, t_list *head)
{
	t_list *iter;
	struct stat buf;

	iter = head;
	while (iter->next)
	{
		stat(join_paths(iter->directory, iter->content), &buf);
		if (S_ISDIR(buf.st_mode) && !ft_strequ(iter->content, "..") && !ft_strequ(iter->content, "."))
		{
			add_directory_to_list(env, join_paths(iter->directory, iter->content), iter);
			recurse_folders(env, iter->down);
		}
		iter = iter->next;
	}
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
	{
		recurse_folders(env, env->head);
		sort_list(env, env->head, &sort_by_alpha);
		print_list(env, env->head);
	}
	else
	{
		sort_list(env, env->head, &sort_by_alpha);
		if (env->t_flag)
			sort_list(env, env->head, &sort_by_time);
		if (env->r_flag)
			sort_list(env, env->head, &sort_by_revalpha);//needs to switch to sort_by_reverse
		print_list(env, env->head);
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
