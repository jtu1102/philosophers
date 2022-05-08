/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 03:42:19 by soahn             #+#    #+#             */
/*   Updated: 2022/05/05 15:01:56 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*dinner(void *args)
{
	t_data	*data;
	t_philo	*philo;

	philo = args;
	data = philo->data;
	if (philo->id % 2 == 1)
		usleep(15000);
	while (data->dead == FALSE)
	{
		philo_eat(data, philo);
		if (data->dead == TRUE)
			break ;
		philo_sleep(data, philo);
		philo_thinking(data, philo);
	}
	return (NULL);
}

void	check_eating_end(t_data *data)
{
	int	i;
	int	eat_max;
	int	check;

	eat_max = data->number_of_times_each_philosopher_must_eat;
	if (eat_max == -1)
		return ;
	check = 0;
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (data->philo[i].eating_cnt >= eat_max)
			check++;
	}
	if (check == data->number_of_philosophers)
		data->dead = TRUE;
}

void	check_philo_dead(t_data *data)
{
	int			i;
	t_philo		*philo;

	philo = data->philo;
	while (!(data->dead))
	{
		i = -1;
		while (++i < data->number_of_philosophers && !(data->dead))
		{
			pthread_mutex_lock(&(data->checking));
			if (get_current_time() - philo[i].last_eat_time > data->time_to_die)
			{
				print_action(data, philo[i].id, "is died");
				data->dead = TRUE;
			}
			check_eating_end(data);
			pthread_mutex_unlock(&(data->checking));
		}
	}
}

void	clear_dinner(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_unlock(&data->fork[data->philo[i].left_fork]);
		pthread_mutex_unlock(&data->fork[data->philo[i].right_fork]);
		pthread_mutex_destroy(&data->fork[i]);
	}
	free(data->fork);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(data->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&data->checking);
	pthread_mutex_destroy(&data->printing);
	free(data->philo);
}

void	start_dinner(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_current_time();
	while (++i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, dinner,
				(void *)&data->philo[i]))
			exit_msg("create thread fail");
		data->philo[i].last_eat_time = get_current_time();
	}
	check_philo_dead(data);
	clear_dinner(data);
}
