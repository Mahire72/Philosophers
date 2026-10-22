/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaimai <mamaimai <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:29:12 by mamaimai          #+#    #+#             */
/*   Updated: 2025/09/21 14:48:00 by mamaimai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0
		|| pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (write(2, "Error: mutex init failed\n", 25), 1);
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (write(2, "Error: fork init failed\n", 24), 1);
		i++;
	}
	return (0);
}

static int	assign_philo(t_philo *philo, t_data *data, int i)
{
	if (!philo || !data)
		return (1);
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->last_meal = data->start_time;
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->nb_philos];
	philo->data = data;
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
		return (1);
	if (pthread_create(&philo->thread, NULL, philo_routine, philo) != 0)
		return (1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;
	int	ret;

	if (!data || !data->philos)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		ret = assign_philo(&data->philos[i], data, i);
		if (ret != 0)
			return (1);
		i++;
	}
	return (0);
}
