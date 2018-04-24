/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 10:44:20 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/23 17:41:23 by nobrien          ###   ########.fr       */
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
	t_list	*head;
}				t_env;

#endif