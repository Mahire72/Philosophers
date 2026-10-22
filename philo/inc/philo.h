/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaimai <mamaimai <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:51:01 by mamaimai          #+#    #+#             */
/*   Updated: 2025/09/21 14:22:17 by mamaimai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_data			*data;
}					t_philo;

struct s_data
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals_to_eat;
	int				is_dead;
	long			start_time;

	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
};

//actions
void	take_left_fork(t_philo *philo);
void	take_right_fork(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);

//args
int		validate_args(int argc, char **argv);
int		fill_data(int argc, char **argv, t_data *data);

//cleanup
void	destroy_resources(t_data *data);

//death_print
int		someone_died(t_data *data);
void	set_dead(t_data *data);
void	print_action(t_philo *philo, const char *msg);

// init
int		init_mutexes(t_data *data);
int		init_philosophers(t_data *data);

//monitor
int		check_philo_death(t_data *data, long now);
int		check_all_full(t_data *data);
void	*monitor_routine(void *arg);

// routine
void	*philo_routine(void *arg);

//threads
void	join_threads(t_data *data, pthread_t monitor);

//utils
long	get_time_ms(void);
void	msleep(t_philo *philo, long ms);
long	ft_atol(const char *str);
int		is_number(const char *str);

#endif /* PHILO_H */
