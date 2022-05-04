/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 10:23:39 by soahn             #+#    #+#             */
/*   Updated: 2022/05/04 00:38:13 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*fork;

	fork = data->fork;
	pthread_mutex_lock(&fork[philo->left_fork]);
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&fork[philo->right_fork]);
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->checking); // 출력 꼬이지 않도록, 죽음 체크하는 부분과 겹치지 않게 보호!!
	print_action(data, philo->id, "is eating");
	pthread_mutex_unlock(&data->checking);
	smart_usleep(data->time_to_eat, data);
	philo->last_eat_time = get_current_time();
	philo->eating_cnt++;
	pthread_mutex_unlock(&fork[philo->left_fork]);
	pthread_mutex_unlock(&fork[philo->right_fork]);
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	print_action(data, philo->id, "is sleeping");
	smart_usleep(data->time_to_sleep, data);
}

void	philo_thinking(t_data *data, t_philo *philo)
{
	print_action(data, philo->id, "is thinking");
}
