/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 19:01:21 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/02 19:43:25 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		is_file(char *str)
{
	struct stat buf;

	stat(str, &buf);
	return (S_ISREG(buf.st_mode));
}

void	array_list_swap(t_env *env, int i)
{
	t_list *tmp;

	tmp = env->head[i - 1];
	env->head[i - 1] = env->head[i];
	env->head[i] = tmp;
}

void	array_str_swap(t_env *env, int i)
{
	char *tmp;

	tmp = env->files[i - 1];
	env->files[i - 1] = env->files[i];
	env->files[i] = tmp;
}

t_list	*new_list_item(void)
{
	t_list *tmp;

	tmp = malloc(sizeof(t_list));
	tmp->next = NULL;
	tmp->content = NULL;
	tmp->content_size = 0;
	tmp->down = NULL;
	return (tmp);
}

void	list_swap(t_list *a, t_list *b)//speed option increase
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
