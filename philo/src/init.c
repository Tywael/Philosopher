/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:39:13 by yalthaus          #+#    #+#             */
/*   Updated: 2022/06/06 11:42:11 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	char	*s;
	int		sign;
	int		rep;

	s = (char *)str;
	sign = 1;
	rep = 0;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s <= '9' && *s >= '0')
	{
		rep = (rep * 10) + (*s - '0');
		s++;
	}
	return (sign * rep);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->nb_philo;
		data->philo[i].count_meal = 0;
		data->philo[i].time_die = 0;
		data->philo[i].data = data;
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	data->end = 0;
	data->philo = malloc((data->nb_philo + 1) * sizeof(t_philo));
	if (!data->philo)
		return (1);
	data->forks = malloc((data->nb_philo + 1) * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (1);
	if (argc == 6)
		data->eat_counter = ft_atoi(argv[5]);
	else
		data->eat_counter = -1;
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (destroy_forks(i, 0, data));
	if (pthread_mutex_init(&(data->message), NULL))
		return (0);
	if (pthread_mutex_init(&(data->eating), NULL))
		return (0);
	return (init_philo(data));
}
