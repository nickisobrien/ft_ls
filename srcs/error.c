/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:11:49 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/02 19:34:46 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

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
