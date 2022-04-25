/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 03:42:19 by soahn             #+#    #+#             */
/*   Updated: 2022/04/26 04:44:15 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*dinner(t_philo *philo)
{
	long long	t;

	if (philo->id % 2 == 1)
	{
		philo->last_eat_time = get_current_time();
		usleep(10000);
	}
	
	while (philo->data->dead == FALSE)
	{
		eat();
		
	}
}

void	check_philo_dead(t_data *data)
{
	int	i;
}

void	end_dinner(t_data *data)
{
	
}

void	start_dinner(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, dinner, &data->philo[i]))
			exit_msg("create thread fail");
	}
	check_philo_dead(data);
	end_dinner(data); // 스레드 정리, 뮤텍스 파괴, 메모리 해제
}