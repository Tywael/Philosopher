/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:38:59 by yalthaus          #+#    #+#             */
/*   Updated: 2022/06/06 11:39:01 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	str_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	philo_clear(t_data *data, char *str)
{
	free(data->forks);
	free(data->philo);
	str_error(str);
	return (1);
}

int	arg_born(t_data *data)
{
	if (data->time_die < 1 || data->time_sleep < 1
		|| data->time_eat < 1 || data->nb_philo < 1)
		return (1);
	return (0);
}

int	init_arg(int argc, char **argv, t_data *data)
{
	int	ret;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_data(data, argc, argv))
		return (1);
	ret = arg_born(data);
	if (ret)
		return (ret);
	return (0);
}
