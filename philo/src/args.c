/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaimai <mamaimai <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:24:34 by mamaimai          #+#    #+#             */
/*   Updated: 2025/09/21 14:26:28 by mamaimai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(2,
			"Usage: ./philo number_of_philos time_to_die time_to_eat "
			"time_to_sleep [number_of_meals]\n", 88);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
		{
			write(2, "Error: arguments must be positive integers\n", 43);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	fill_mandatory_data(char **argv, t_data *data)
{
	long	tmp;

	tmp = ft_atol(argv[1]);
	if (tmp <= 0 || tmp > INT_MAX)
	{
		write(2, "Error: invalid number_of_philos\n", 32);
		return (1);
	}
	data->nb_philos = (int)tmp;
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
	{
		write(2, "Error: time values must be positive\n", 36);
		return (1);
	}
	return (0);
}

static int	fill_optional_data(int argc, char **argv, t_data *data)
{
	long	tmp;

	if (argc == 6)
	{
		tmp = ft_atol(argv[5]);
		if (tmp <= 0)
		{
			write(2, "Error: number_of_meals must be positive\n", 40);
			return (1);
		}
		data->nb_meals_to_eat = (int)tmp;
	}
	else
		data->nb_meals_to_eat = -1;
	return (0);
}

int	fill_data(int argc, char **argv, t_data *data)
{
	if (fill_mandatory_data(argv, data))
		return (1);
	if (fill_optional_data(argc, argv, data))
		return (1);
	return (0);
}
