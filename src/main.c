/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:22:23 by soahn             #+#    #+#             */
/*   Updated: 2022/04/26 03:42:03 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	init_arg(&data, argc, argv);
	init_data(&data, argc, argv);
	start_dinner(&data);
	return (0);
}