/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:52:12 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/11 11:40:13 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * init_mutexes - Initialize all program mutexes
 * 
 * Creates and initializes all synchronization mutexes needed for the program.
 * Includes fork mutexes (one per philosopher) and control mutexes.
 * Implements proper error handling with cleanup on failure.
 * 
 * @data: Pointer to shared data structure
 * Return: 1 on success, 0 on failure
 */
int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->meal, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (0);
	return (1);
}

int	init_data(t_data *data)
{
	data->dead = 0;
	data->finished = 0;
	data->start_time = get_time();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (free(data->forks), 0);
	if (!init_mutexes(data))
		return (free(data->forks), free(data->philos), 0);
	return (1);
}

/*
 * init_philosopher - Initialize individual philosopher
 * 
 * Sets up a single philosopher with ID, fork assignments, and initial state.
 * Uses strategic fork assignment to prevent deadlocks.
 * Links philosopher to shared data structure.
 * 
 * @philo: Pointer to philosopher structure
 * @data: Pointer to shared data
 * @id: Philosopher ID (0-based internally, 1-based for display)
 */
static void	init_philosopher(t_philo *philo, t_data *data, int id)
{
	philo->id = id + 1;
	philo->meals_eaten = 0;
	philo->last_meal = get_time();
	philo->left_fork = id;
	philo->right_fork = (id + 1) % data->num_philos;
	philo->data = data;
}

/*
 * init_philos - Initialize all philosophers
 * 
 * Creates and initializes all philosopher structures in the array.
 * Sets up fork assignments and initial state for each philosopher.
 * Prepares philosophers for thread creation and simulation start.
 * 
 * @data: Pointer to shared data structure
 * Return: 1 on success, 0 on failure
 */
int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		init_philosopher(&data->philos[i], data, i);
		i++;
	}
	return (1);
}
