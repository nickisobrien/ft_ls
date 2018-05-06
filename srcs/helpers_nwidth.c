/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_nwidth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:09:27 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/06 15:30:00 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int	num_len(unsigned int x)
{
	if (x >= 1000000000)
		return (10);
	if (x >= 100000000)
		return (9);
	if (x >= 10000000)
		return (8);
	if (x >= 1000000)
		return (7);
	if (x >= 100000)
		return (6);
	if (x >= 10000)
		return (5);
	if (x >= 1000)
		return (4);
	if (x >= 100)
		return (3);
	if (x >= 10)
		return (2);
	return (1);
}

int			get_size_len(t_list *base)
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
		if (num_len(buf.st_size) > total)
			total = num_len(buf.st_size);
		iter = iter->next;
	}
	return (total);
}

int			get_size_len_arr(t_env *env)
{
	int			i;
	int			total;
	struct stat	buf;

	i = -1;
	total = 0;
	while (++i < env->has_file)
	{
		stat(env->files[i], &buf);
		if (num_len(buf.st_size) > total)
			total = num_len(buf.st_size);
	}
	return (total);
}
