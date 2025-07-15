/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:52:32 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/15 20:02:43 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos % 2 == 1)
	{
		if (philo->id % 2 == 1)
			ft_usleep(philo->data->time_to_eat / 2, philo->data);
	}
	else
	{
		if (philo->id % 2 == 0)
			ft_usleep(1, philo->data);
	}
	while (!is_simulation_over(philo->data))
	{
		eat(philo);
		if (is_simulation_over(philo->data))
			break ;
		sleep_and_think(philo);
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
