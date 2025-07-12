/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:52:12 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/12 10:21:21 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_data *data)
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

int	init_philos(t_data *data)
{
	t_philo	*philo;
	int	i;
	
	i = 0;
	while (i < data->num_philos)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal = get_time();
		philo->left_fork = i;
		philo->right_fork = (i + 1) % data->num_philos;
		philo->data = data;
		i++;
	}
	return (1);
}
