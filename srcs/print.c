/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:15:08 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/03 17:15:53 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	print_permissions(struct stat abuf)
{
	ft_printf((S_ISDIR(abuf.st_mode)) ? "d" : "-");
	ft_printf((abuf.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((abuf.st_mode & S_IWUSR) ? "w" : "-");
	ft_printf((abuf.st_mode & S_IXUSR) ? "x" : "-");
	ft_printf((abuf.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((abuf.st_mode & S_IWGRP) ? "w" : "-");
	ft_printf((abuf.st_mode & S_IXGRP) ? "x" : "-");
	ft_printf((abuf.st_mode & S_IROTH) ? "r" : "-");
	ft_printf((abuf.st_mode & S_IWOTH) ? "w" : "-");
	ft_printf((abuf.st_mode & S_IXOTH) ? "x" : "-");
}

void	print_l_info(char *str)
{
	struct stat		buf;
	char			*t;

	t = ft_strnew(12);
	stat(str, &buf);
	print_permissions(buf);
	ft_printf(" %2d", buf.st_nlink);
	ft_printf(" %s ", getpwuid(buf.st_uid)->pw_name);
	ft_printf(" %s ", getgrgid(buf.st_gid)->gr_name);
	ft_printf(" %5d", buf.st_size);
	ft_strncpy(t, ctime(&(buf.st_mtime)) + 4, 12);
	ft_printf(" %.12s ", t);
	ft_strdel(&t);
	ft_strdel(&str);
}

int		get_total(t_list *base)
{
	t_list			*iter;
	int				total;
	struct stat		buf;
	char			*str;

	iter = base;
	total = 0;
	while (iter->next)
	{
		str = join_paths(iter->directory, iter->content);
		stat(str, &buf);
		ft_strdel(&str);
		total += buf.st_blocks;
		iter = iter->next;
	}
	return (total);
}

void	print_list(t_env *env, t_list *base)
{
	t_list	*iter;

	iter = base;
	if (env->arg_count > 1 || (env->R_flag && env->head[0] != base))
		ft_printf("%s:\n", iter->directory);
	if (env->l_flag)
		ft_printf("total %d\n", get_total(base));
	while (iter->next)
	{
		if (env->l_flag)
			print_l_info(join_paths(iter->directory, iter->content));
		ft_printf("%-10s ", iter->content);
		if (env->l_flag && iter->next->next)
			ft_printf("\n");
		iter = iter->next;
	}
	iter = base;
	while (iter->next)
	{
		if (iter->down)
		{
			ft_printf("\n\n");
			print_list(env, iter->down);
		}
		iter = iter->next;
	}
}

void	print_file(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->has_file)
	{
		if (env->l_flag && i)
			ft_printf("\n");
		if (env->l_flag)
			print_l_info(env->files[i]);
		ft_printf("%-10s ", env->files[i]);
	}
}
