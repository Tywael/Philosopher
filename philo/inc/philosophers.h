/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 00:50:06 by yalthaus          #+#    #+#             */
/*   Updated: 2022/06/06 11:38:05 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		time_die;
	int				count_meal;
	int				eat_counter;
	struct s_data	*data;
	pthread_t		thread_id;
}				t_philo;

typedef struct s_data
{
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				dead;
	int				end;
	int				eat_counter;
	int				nb_philo;
	long long		init_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	eating;
	t_philo			*philo;
}				t_data;

//Error
int			philo_clear(t_data *data, char *str);
int			str_error(char *str);
int			init_arg(int argc, char **argv, t_data *data);

//Init
int			init_data(t_data *data, int argc, char **argv);
int			init_mutex(t_data *data);
int			init_philo(t_data *data);

//Tools
void		sleep_timer(long long time_to, t_data *data);
void		print_message(t_data *data, int id, char *str);
long long	timestamp(void);
long long	delta_time(long long flag, long long time_spent);
int			destroy_forks(int i, int ret, t_data *data);

//Resolve
void		philo_lunch(t_philo *philo, t_data *data);
void		*day(void *philo_addr);
void		death_checker(t_data *data, t_philo *philo, int i);
void		exit_solver(t_data *data, t_philo *philo);
int			process(t_data *data);



#endif
