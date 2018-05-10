/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 21:37:00 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/09 21:37:30 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void			handle_file(t_env *env, char *str)
{
	env->files[env->has_file] = ft_strdup(str);
	env->has_file++;
}

int				is_file(char *str)
{
	struct stat buf;

	stat(str, &buf);
	return (S_ISREG(buf.st_mode));
}
