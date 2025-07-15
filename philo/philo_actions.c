/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:52:24 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/15 20:01:32 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_meal_data(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	if (philo->data->must_eat != -1
		&& philo->meals_eaten >= philo->data->must_eat)
	{
		pthread_mutex_unlock(&philo->data->meal);
		return ;
	}
	pthread_mutex_unlock(&philo->data->meal);
}

void	eat(t_philo *philo)
{
	if (is_simulation_over(philo->data))
		return ;
	if (!take_forks(philo))
		return ;
	if (is_simulation_over(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		return ;
	}
	print_status(philo, EATING);
	update_meal_data(philo);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	sleep_and_think(t_philo *philo)
{
	long long	think_time;

	if (!check_and_print_sleeping(philo))
		return ;
	ft_usleep(philo->data->time_to_sleep, philo->data);
	if (is_simulation_over(philo->data))
		return ;
	check_and_print_thinking(philo);
	if (philo->data->num_philos % 2 == 1)
	{
		think_time = (philo->data->time_to_eat * 2)
			- philo->data->time_to_sleep;
		if (think_time > 0)
			ft_usleep(think_time / 2, philo->data);
	}
}
