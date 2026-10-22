/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaimai <mamaimai <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:30:45 by mamaimai          #+#    #+#             */
/*   Updated: 2025/09/21 14:30:47 by mamaimai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_data *data, long now)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (now - data->philos[i].last_meal > data->time_to_die)
		{
			print_action(&data->philos[i], "died");
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			set_dead(data);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	return (0);
}

int	check_all_full(t_data *data)
{
	int	i;
	int	all_full;

	if (data->nb_meals_to_eat == -1)
		return (0);
	all_full = 1;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten < data->nb_meals_to_eat)
			all_full = 0;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	if (all_full)
		set_dead(data);
	return (all_full);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	long	now;

	data = (t_data *)arg;
	while (!someone_died(data))
	{
		now = get_time_ms();
		if (check_philo_death(data, now))
			return (NULL);
		if (check_all_full(data))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
