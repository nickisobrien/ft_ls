/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:15:57 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/01 20:04:00 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

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

void	sort_list(t_env *env, t_list *base, int (*cmp)(t_list *, t_list *))
{
	t_list		*iter;
	int			unsorted;
	int			equals;

	equals = env->r_flag ? 0 : 1; 
	unsorted = 1;
	while (unsorted)
	{
		unsorted = 0;
		iter = base;
		while (iter->next && iter->next->next)
		{
			if ((*cmp)(iter, iter->next) == equals)
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
		{
			sort_list(env, iter->down, cmp);
		}
		iter = iter->next;
	}
}


void	array_list_swap(t_env *env, int i)
{
	t_list *tmp;
	
	tmp = env->head[i - 1];
	env->head[i - 1] = env->head[i];
	env->head[i] = tmp;
}

void	sort_list_array(t_env *env, int (*cmp)(t_list *, t_list *))
{
	int			i;
	int			unsorted;
	int			equals;

	equals = env->r_flag ? 0 : 1; 
	unsorted = 1;
	while (unsorted)
	{
		unsorted = 0;
		i = 0;
		while (++i < env->index)
		{
			if ((*cmp)(env->head[i - 1], env->head[i]) == equals)
			{
				unsorted = 1;
				array_list_swap(env, i);
			}
		}
	}
}

void	array_str_swap(t_env *env, int i)
{
	char *tmp;
	
	tmp = env->files[i - 1];
	env->files[i - 1] = env->files[i];
	env->files[i] = tmp;
}

void	sort_str_array(t_env *env, int (*cmp)(char *, char *))
{
	int			i;
	int			unsorted;
	int			equals;

	equals = env->r_flag ? 0 : 1; 
	unsorted = 1;
	while (unsorted)
	{
		unsorted = 0;
		i = 0;
		while (++i < env->has_file)
		{
			if ((*cmp)(env->files[i - 1], env->files[i]) == equals)
			{
				unsorted = 1;
				array_str_swap(env, i);
			}
		}
	}
}

