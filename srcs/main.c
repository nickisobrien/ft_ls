/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 10:42:10 by nobrien           #+#    #+#             */
/*   Updated: 2018/05/01 17:56:23 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		main(int argc, char **argv)
{
	t_env env;

	init_env(&env);
	handle_flags(&env, argc, argv);
	handle_args(&env, argc, argv);
	ft_printf("\n");
	return (0);
}
