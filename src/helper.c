/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:41:53 by soahn             #+#    #+#             */
/*   Updated: 2022/05/04 09:37:29 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	long	result;
	size_t	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

void	exit_msg(char *msg)
{
	printf(RED);
	printf("[Error]");
	printf("%s", msg);
	printf(RESET);
	exit(EXIT_ERROR);
}

long long	get_current_time(void)
{
	struct timeval	tv;
	long long		current;

	gettimeofday(&tv, NULL);
	current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current);
}

void	smart_usleep(long long time, t_data *data)
{
	long long	start;

	start = get_current_time();
	while (data->dead == FALSE)
	{
		if (get_current_time() - start >= time)
			break ;
		usleep(10);
	}
}

void	print_action(t_data *data, int id, char *action)
{
	pthread_mutex_lock(&data->printing);
	if (data->dead == FALSE)
	{
		printf("%lld", get_current_time() - data->start_time);
		printf(" %d ", id + 1);
		printf("%s", action);
		printf("\n");
	}
	pthread_mutex_unlock(&data->printing);
}
