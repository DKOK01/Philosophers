/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:52:32 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/13 10:21:07 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * is_dead - Check if a philosopher has died
 * 
 * Thread-safe check for philosopher death based on time since last meal.
 * Uses mutex protection to safely read last meal time.
 * 
 * @philo: Pointer to philosopher to check
 * Return: 1 if dead, 0 if alive
 */
int	is_dead(t_philo *philo)
{
	long long	current_time;
	long long	time_since_meal;

	pthread_mutex_lock(&philo->data->meal);
	current_time = get_time();
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal);
	return (time_since_meal > philo->data->time_to_die);
}

/*
 * all_ate_enough - Check if all philosophers ate enough meals
 * 
 * Verifies if all philosophers have reached the required meal count.
 * Returns false if no meal limit is set (must_eat == -1).
 * Uses thread-safe access to meal counts.
 * 
 * @data: Pointer to shared data structure
 * Return: 1 if all ate enough, 0 otherwise
 */
int	all_ate_enough(t_data *data)
{
	int	i;

	if (data->must_eat == -1)
		return (0);
	pthread_mutex_lock(&data->meal);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat)
		{
			pthread_mutex_unlock(&data->meal);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal);
	return (1);
}

/*
 * print_death - Print death message for a philosopher
 * 
 * Thread-safe printing of death message with proper timestamp.
 * Only prints if no previous death was detected.
 * 
 * @philo: Pointer to the philosopher who died
 */
static void	print_death(t_philo *philo)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->dead)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, DIED);
	}
	pthread_mutex_unlock(&philo->data->print);
}

/*
 * monitor - Death and completion monitoring thread
 * 
 * Continuously monitors all philosophers for death or completion.
 * Runs as a separate thread to provide responsive death detection.
 * Terminates simulation when death or completion is detected.
 * 
 * @arg: Pointer to shared data structure (cast from void*)
 * Return: NULL when monitoring is complete
 */
void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->dead && !data->finished)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (is_dead(&data->philos[i]))
			{
				print_death(&data->philos[i]);
				pthread_mutex_lock(&data->dead_lock);
				data->dead = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return (NULL);
			}
			i++;
		}
		if (all_ate_enough(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->finished = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

/*
 * philosopher - Main philosopher thread routine
 * 
 * Implements the philosopher's life cycle: eat, sleep, think.
 * Runs until death is detected or meal requirements are met.
 * Includes timing optimization for even/odd philosophers.
 * 
 * @arg: Pointer to philosopher structure (cast from void*)
 * Return: NULL when philosopher routine is complete
 */
void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);
	while (!philo->data->dead && !philo->data->finished)
	{
		eat(philo);
		if (philo->data->dead || philo->data->finished)
			break ;
		sleep_and_think(philo);
		if (philo->data->must_eat != -1
			&& philo->meals_eaten >= philo->data->must_eat)
			break ;
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
		return (0);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (1);
}
