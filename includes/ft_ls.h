/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 10:44:20 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/30 15:17:20 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_LS_H
# define __FT_LS_H

#include "../libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

typedef struct 	s_env
{
	int		l_flag;
	int		R_flag;
	int		a_flag;
	int		t_flag;
	int		r_flag;
	int		flag_count;
	int		arg_count;
	t_list	*head;
}				t_env;

//directories.c
void	recurse_folders(t_env *env, t_list *head);
void	add_directory_to_list(t_env *env, char *directory, t_list *base);

//error.c
void	error(char *err);
void	usage(void);
DIR		*open_dir(char *directory);
void	close_dir(DIR *dir);
char	*join_paths(char *path_a, char *path_b);

//init.c
void	init_env(t_env *env);
void	handle_flags(t_env *env, int argc, char **argv);
void	handle_args(t_env *env, int argc, char **args);

//print.c
void	print_permissions(struct stat abuf);
void	print_l_info(t_list *item);
void	print_list(t_env *env, t_list *base);

//lists.c
t_list	*new_list_item(void);
void	list_swap(t_list *a, t_list *b);
void	sort_list(t_env *env, t_list *base, int (*cmp)(t_list *, t_list *));

//sort_by.c
int		sort_by_alpha(t_list *a, t_list *b);
int		sort_by_time(t_list *a, t_list *b);

#endif