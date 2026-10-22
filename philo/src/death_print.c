/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaimai <mamaimai <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:18:49 by mamaimai          #+#    #+#             */
/*   Updated: 2025/09/21 14:28:36 by mamaimai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	someone_died(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_lock);
	dead = data->is_dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (dead);
}

void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->is_dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

void	print_action(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (!philo->data->is_dead)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d %s\n",
			get_time_ms() - philo->data->start_time,
			philo->id,
			msg);
		pthread_mutex_unlock(&philo->data->write_lock);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
}
