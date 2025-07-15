/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:26:15 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/15 11:02:44 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	long long	current_time;
	long long	time_since_meal;

	pthread_mutex_lock(&philo->data->meal);
	current_time = get_time();
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal);
	return (time_since_meal > philo->data->time_to_die);
}

static int	all_ate_enough(t_data *data)
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

static void	print_death(t_philo *philo)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print);
	timestamp = get_time() - philo->data->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, DIED);
	pthread_mutex_unlock(&philo->data->print);
}

static int	check_deaths(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (is_dead(&data->philos[i]))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			print_death(&data->philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->dead && !data->finished)
	{
		if (check_deaths(data))
			return (NULL);
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
