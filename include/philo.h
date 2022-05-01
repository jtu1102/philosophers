/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 00:28:06 by soahn             #+#    #+#             */
/*   Updated: 2022/05/02 05:58:41 by soahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h> //todo: include 어떤 함수 때문인지 확인할 것
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // printf 허용되어 있음
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define EXIT_ERROR 1

# define RED     "\x1b[31m"
// # define GREEN   "\x1b[32m"
// # define YELLOW  "\033[0;33m"
// # define BLUE    "\x1b[34m"
// # define MAGENTA "\x1b[35m"
// # define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"


typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_eat_time; // 얼마나 대기했는지 체크하기 위한 함수
	pthread_t		thread_id;
	int				eating_cnt; // t/f 로 먹을 횟수만큼 먹었는지 (마지막 인자 있을 때!)
	struct s_data	*data; // pthread_create 인자 함수의 argument로 하나밖에 줄 수 없어서 여기다가 data 정보도 넣어줌
}				t_philo;

typedef struct s_data
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					eating_end;
	int					dead;
	long long			start_time;
	pthread_mutex_t		*fork;
	pthread_mutex_t		printing;
	pthread_mutex_t		mu;
	t_philo				*philo;
}			t_data;

/*action.c*/
void	philo_eat(t_data *data, t_philo *philo);
void	philo_sleep(t_data *data, t_philo *philo);
void	philo_thinking(t_data *data, t_philo *philo);

/*dinner.c*/
void	start_dinner(t_data *data);

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