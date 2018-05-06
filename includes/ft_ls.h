/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 10:44:20 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/03 17:13:45 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_LS_H
# define __FT_LS_H

# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

typedef struct	s_env
{
	int			l_flag;
	int			ur_flag;
	int			a_flag;
	int			t_flag;
	int			r_flag;
	int			flag_count;
	int			arg_count;
	int			index;
	int			has_file;
	char		**files;
	t_list		**head;
}				t_env;

int				is_file(char *str);
void			array_list_swap(t_env *env, int i);
void			array_str_swap(t_env *env, int i);
t_list			*new_list_item(void);

void			recurse_folders(t_env *env, t_list *head);
void			add_directory_to_list(t_env *env,
	char *directory, t_list *base);
int				get_total(t_list *base);

void			error(char *err);
void			usage(void);
DIR				*open_dir(char *directory);
void			close_dir(DIR *dir);
char			*join_paths(char *path_a, char *path_b);

void			init_env(t_env *env);
void			malloc_llarr(t_env *env);

void			handle_flags(t_env *env, int argc, char **argv);
void			handle_args(t_env *env, int argc, char **args);

void			print_permissions(struct stat abuf);
void			print_list(t_env *env, t_list *base);
void			print_file(t_env *env);

void			list_swap(t_list *a, t_list *b);
void			sort_list(t_env *env, t_list *base,
	int (*cmp)(t_list *, t_list *));
void			sort_list_array(t_env *env, int (*cmp)(t_list *, t_list *));
void			sort_str_array(t_env *env, int (*cmp)(char *, char *));

int				sort_by_alpha(t_list *a, t_list *b);
int				sort_by_time(t_list *a, t_list *b);
int				str_sort_by_alpha(char *a, char *b);
int				str_sort_by_time(char *a, char *b);

int				get_size_len(t_list *base);
int				get_size_len_arr(t_env *env);
#endif
