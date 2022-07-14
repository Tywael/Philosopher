/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:44:01 by yalthaus          #+#    #+#             */
/*   Updated: 2022/06/06 11:44:12 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_lunch(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	print_message(data, philo->id, "has taken a left fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	print_message(data, philo->id, "has taken a right fork");
	pthread_mutex_lock(&(data->eating));
	print_message(data, philo->id, "is eating");
	philo->time_die = timestamp();
	pthread_mutex_unlock(&(data->eating));
	sleep_timer(data->time_eat, data);
	(philo->count_meal)++;
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void	*day(void *philo_addr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_addr;
	data = philo->data;
	if (philo->id % 2)
		usleep(10000);
	while (!(data->dead))
	{
		philo_lunch(philo, data);
		if (data->end)
			break ;
		print_message(data, philo->id, "is sleeping");
		sleep_timer(data->time_sleep, data);
		print_message(data, philo->id, "is thinking");
	}
	return (NULL);
}

void	end_solver(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo && data->nb_philo > 1)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->message));
}

void	alive_checker(t_data *data, t_philo *philo, int i)
{
	while (!(data->end))
	{
		i = -1;
		while (++i < data->nb_philo && !(data->dead))
		{
			pthread_mutex_lock(&(data->eating));
			if (delta_time(philo[i].time_die,
					timestamp()) > data->time_die)
			{
				print_message(data, i, "died");
				data->dead = 1;
			}
			pthread_mutex_unlock(&(data->eating));
			usleep(100);
		}
		if (data->dead)
			break ;
		i = 0;
		while (data->eat_counter != -1 && i < data->nb_philo
			&& philo[i].count_meal >= data->eat_counter - 1)
			i++;
		if (i == data->nb_philo)
			data->end = 1;
	}
}

int	process(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philo;
	data->init_time = timestamp();
	while (++i < data->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, day, &(philo[i])))
			return (0);
		philo[i].time_die = timestamp();
	}
	alive_checker(data, data->philo, 0);
	end_solver(data, philo);
	return (1);
}
