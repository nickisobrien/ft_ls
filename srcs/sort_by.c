/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_by.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:16:43 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/01 20:10:05 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		sort_by_alpha(t_list *a, t_list *b)
{
	return ((ft_strcmp(a->content, b->content)) > 0);
}

int		sort_by_time(t_list *a, t_list *b)
{
	struct stat		abuf;
	struct stat		bbuf;

	stat(join_paths(a->directory, a->content), &abuf);
	stat(join_paths(b->directory, b->content), &bbuf);
	if ((abuf.st_mtimespec.tv_sec == bbuf.st_mtimespec.tv_sec &&
			abuf.st_mtimespec.tv_nsec == bbuf.st_mtimespec.tv_nsec))
		return (sort_by_alpha(a, b));
	return (abuf.st_mtimespec.tv_sec < bbuf.st_mtimespec.tv_sec ||
		(abuf.st_mtimespec.tv_sec == bbuf.st_mtimespec.tv_sec &&
			abuf.st_mtimespec.tv_nsec < bbuf.st_mtimespec.tv_nsec));
}

int		str_sort_by_alpha(char *a, char *b)
{
	return ((ft_strcmp(a, b)) > 0);
}

int		str_sort_by_time(char *a, char *b)
{
	struct stat		abuf;
	struct stat		bbuf;

	stat(a, &abuf);
	stat(b, &bbuf);
	if ((abuf.st_mtimespec.tv_sec == bbuf.st_mtimespec.tv_sec &&
			abuf.st_mtimespec.tv_nsec == bbuf.st_mtimespec.tv_nsec))
		return (str_sort_by_alpha(a, b));
	return (abuf.st_mtimespec.tv_sec < bbuf.st_mtimespec.tv_sec ||
		(abuf.st_mtimespec.tv_sec == bbuf.st_mtimespec.tv_sec &&
			abuf.st_mtimespec.tv_nsec < bbuf.st_mtimespec.tv_nsec));
}