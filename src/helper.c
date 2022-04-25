/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:41:53 by soahn             #+#    #+#             */
/*   Updated: 2022/04/26 03:53:10 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	else
		return (FALSE);
}

int	ft_atoi(const char *str)
{
	long	result;
	size_t	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == FALSE)
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
	printf(msg);
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

void	print_action(t_data *data, int id, char *action)
{
	pthread_mutex_lock(&data->printing);
	printf("%ld", get_current_time());
	printf(" %d ", id);
	printf(action);
	printf("\n");
	pthread_mutex_unlock(&data->printing);
}