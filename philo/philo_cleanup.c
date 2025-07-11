/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:52:43 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/11 11:21:14 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * destroy_mutexes - Destroy all initialized mutexes
 * 
 * Safely destroys all mutexes that were successfully initialized.
 * Handles fork mutexes and control mutexes separately.
 * Prevents errors from destroying uninitialized mutexes.
 * 
 * @data: Pointer to shared data structure
 */
void	destroy_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->dead_lock);
}

/*
 * cleanup - Clean up all allocated resources
 * 
 * Comprehensive cleanup function that handles all program resources.
 * Destroys mutexes, frees allocated memory, and resets pointers.
 * Safe to call multiple times or on partially initialized data.
 * 
 * @data: Pointer to shared data structure
 */
void	cleanup(t_data *data)
{
	destroy_mutexes(data);
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
