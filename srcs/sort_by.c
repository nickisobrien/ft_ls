/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_by.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:16:43 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/27 18:16:51 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

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
	// if ((abuf.st_mtimespec.tv_sec == bbuf.st_mtimespec.tv_sec &&
	// 		abuf.st_mtimespec.tv_nsec == bbuf.st_mtimespec.tv_nsec))
	// 	return (2); // need to figure out this case
	return (abuf.st_mtimespec.tv_sec < bbuf.st_mtimespec.tv_sec ||
		(abuf.st_mtimespec.tv_sec == bbuf.st_mtimespec.tv_sec &&
			abuf.st_mtimespec.tv_nsec < bbuf.st_mtimespec.tv_nsec));
}