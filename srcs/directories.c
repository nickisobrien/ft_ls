/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:13:08 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/03 17:21:49 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

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
	t_list		*iter;
	struct stat	buf;
	char		*str;

	iter = head;
	while (iter->next)
	{
		str = join_paths(iter->directory, iter->content);
		stat(str, &buf);
		if (S_ISDIR(buf.st_mode) && !ft_strequ(iter->content, "..") && !ft_strequ(iter->content, "."))
		{
			add_directory_to_list(env, str, iter);
			recurse_folders(env, iter->down);
		}
		ft_strdel(&str);
		iter = iter->next;
	}
}
