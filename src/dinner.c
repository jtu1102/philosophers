/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 03:42:19 by soahn             #+#    #+#             */
/*   Updated: 2022/05/01 00:57:10 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*dinner(void *args)
{
	t_data	*data;
	t_philo	*philo;

	philo = args;
	data = philo->data;
	philo->last_eat_time = get_current_time(); // 시뮬레이션 시작 시간 저장 !
	if (philo->id % 2 == 1) // 짝수부터 시작
		usleep(1000);
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
	int	max;

	max = -1;
	i = 0;
	while (++i < data->number_of_philosophers)
	{
		if (data->philo[i - 1].eating_cnt != data->philo[i].eating_cnt)
			return ;
	}
	if (data->philo[i - 1].eating_cnt \
	== data->number_of_times_each_philosopher_must_eat)
		data->eating_end = TRUE;
}

void	check_philo_dead(t_data *data)
{
	int			i;
	t_philo		*philo;

	philo = data->philo;
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		long long gap = get_current_time() - philo[i].last_eat_time;
		if (gap > data->time_to_die)
		{
			printf("dead: %lld\n", gap);
			data->dead = TRUE;
		}
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
		usleep(10);
	}
	while (data->dead == FALSE)
	{
		check_eating_end(data);
		check_philo_dead(data);
		usleep(10);
	}
	clear_dinner(data); // 스레드 정리, 뮤텍스 파괴, 메모리 해제
}