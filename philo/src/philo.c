/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:42:31 by yalthaus          #+#    #+#             */
/*   Updated: 2022/06/06 11:43:42 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	ret = init_arg(argc, argv, &data);
	if (ret == 1)
		return (str_error("Error arguments\n"));
	if (ret == 2)
		return (philo_clear(&data, "Error arguments\n"));
	if (!init_mutex(&data))
		return (philo_clear(&data, "Init mutex failed\n"));
	if (!process(&data))
		return (philo_clear(&data, "Resolve failed\n"));
	free(data.forks);
	free(data.philo);
	return (EXIT_SUCCESS);
}
