/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:45:49 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/15 20:02:52 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_over(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->dead_lock);
	result = data->dead || data->finished;
	pthread_mutex_unlock(&data->dead_lock);
	return (result);
}

int	check_and_print_sleeping(t_philo *philo)
{
	long long	timestamp;
	int			should_continue;

	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->dead_lock);
	should_continue = !philo->data->dead;
	if (should_continue)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, SLEEPING);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->data->print);
	return (should_continue);
}

void	check_and_print_thinking(t_philo *philo)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (!philo->data->dead)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, THINKING);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->data->print);
}
