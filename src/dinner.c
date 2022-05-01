/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 03:42:19 by soahn             #+#    #+#             */
/*   Updated: 2022/05/02 07:01:01 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*dinner(void *args)
{
	t_data	*data;
	t_philo	*philo;

	philo = args;
	data = philo->data;
	if (philo->id % 2 == 1) // 짝수부터 시작
		usleep(10000);
	while (data->dead == FALSE) // 무한루프 돌리기
	{
		philo_eat(data, philo);
		if (data->eating_end == TRUE)
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
		data->eating_end = TRUE;
}

void	check_philo_dead(t_data *data)
{
	int			i;
	t_philo		*philo;

	philo = data->philo;
	i = -1;
	while (++i < data->number_of_philosophers && !(data->dead))
	{
		pthread_mutex_lock(&(data->mu));
		if (get_current_time() - philo[i].last_eat_time > data->time_to_die)
		{
			print_action(data, philo[i].id, "is died");
			data->dead = TRUE;	
		}
		pthread_mutex_unlock(&(data->mu));
		usleep(10);
	}
		
}

void	clear_dinner(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		pthread_mutex_unlock(&data->fork[i]);
		pthread_mutex_destroy(&data->fork[i]);
	}
	free(data->fork);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(data->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&data->mu);
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
		if (pthread_create(&data->philo[i].thread_id, NULL, dinner, (void *)&data->philo[i]))
			exit_msg("create thread fail");
		data->philo[i].last_eat_time = get_current_time(); // 시뮬레이션 시작 시간 저장 !
		usleep(10);
	}
	while (data->eating_end == FALSE)
	{
		check_philo_dead(data);
		check_eating_end(data);
	}
	clear_dinner(data); // 스레드 정리, 뮤텍스 파괴, 메모리 해제
}