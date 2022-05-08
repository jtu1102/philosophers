/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:07:10 by soahn             #+#    #+#             */
/*   Updated: 2022/05/08 11:02:45 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_arg(t_data *data, int argc, char **argv)
{
	int	i;
	int	int_arr[7];

	if (!(argc == 5 || argc == 6))
		exit_msg("wrong number of arguments");
	i = 0;
	while (++i < argc)
	{
		int_arr[i] = ft_atoi(argv[i]);
		if (int_arr[i] <= 0)
			exit_msg("wrong argument");
	}
	data->number_of_philosophers = int_arr[1];
	data->time_to_die = int_arr[2];
	data->time_to_eat = int_arr[3];
	data->time_to_sleep = int_arr[4];
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = int_arr[5];
	else if (argc == 5)
		data->number_of_times_each_philosopher_must_eat = -1;
}

void	init_mutex(t_data *data)
{
	int	i;
	int	n;

	n = data->number_of_philosophers;
	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	i = -1;
	while (++i < n)
		if (pthread_mutex_init(&(data->fork[i]), NULL))
			exit_msg("initialize mutex fail");
	if (pthread_mutex_init(&data->printing, NULL))
		exit_msg("initialize mutex fail");
	if (pthread_mutex_init(&data->checking, NULL))
		exit_msg("initialize mutex fail");
}

void	init_philo(t_data *data)
{
	int	i;
	int	n;

	n = data->number_of_philosophers;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * n);
	i = -1;
	while (++i < n)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % n;
		data->philo[i].last_eat_time = 0;
		data->philo[i].thread_id = 0;
		data->philo[i].eating_cnt = 0;
		data->philo[i].data = data;
	}
}

void	init_data(t_data *data)
{
	data->dead = FALSE;
	data->start_time = 0;
	init_mutex(data);
	init_philo(data);
}
