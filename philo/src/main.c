/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaimai <mamaimai <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:30:22 by mamaimai          #+#    #+#             */
/*   Updated: 2025/09/21 14:30:24 by mamaimai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (validate_args(argc, argv))
		return (1);
	if (fill_data(argc, argv, &data))
		return (1);
	data.is_dead = 0;
	data.start_time = get_time_ms();
	data.forks = malloc(sizeof(pthread_mutex_t) * data.nb_philos);
	data.philos = malloc(sizeof(t_philo) * data.nb_philos);
	if (!data.forks || !data.philos)
		return (write(2, "Error: malloc failed\n", 21), 1);
	if (init_mutexes(&data))
		return (1);
	init_philosophers(&data);
	pthread_create(&monitor, NULL, monitor_routine, &data);
	join_threads(&data, monitor);
	destroy_resources(&data);
	return (0);
}
