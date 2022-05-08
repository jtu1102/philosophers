/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 00:28:06 by soahn             #+#    #+#             */
/*   Updated: 2022/05/05 13:45:20 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define EXIT_ERROR 1

# define RED     "\x1b[31m"
# define RESET   "\x1b[0m"

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_eat_time;
	pthread_t		thread_id;
	int				eating_cnt;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					dead;
	long long			start_time;
	pthread_mutex_t		*fork;
	pthread_mutex_t		printing;
	pthread_mutex_t		checking;
	t_philo				*philo;
}			t_data;

/*action.c*/
void		philo_eat(t_data *data, t_philo *philo);
void		philo_sleep(t_data *data, t_philo *philo);
void		philo_thinking(t_data *data, t_philo *philo);

/*dinner.c*/
void		start_dinner(t_data *data);

/*helper.c*/
int			ft_atoi(const char *str);
void		exit_msg(char *msg);
long long	get_current_time(void);
void		smart_usleep(long long time, t_data *data);
void		print_action(t_data *data, int id, char *action);

/*init.c*/
void		init_arg(t_data *data, int argc, char **argv);
void		init_data(t_data *data);

#endif
