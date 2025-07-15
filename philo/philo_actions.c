/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:52:24 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/15 11:46:11 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[0]);
	print_status(philo, FORK);
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(&philo->data->forks[0]);
}

int	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->data->num_philos == 1)
	{
		handle_single_philo(philo);
		return (0);
	}
	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, FORK);
	if (philo->data->dead)
		return (pthread_mutex_unlock(&philo->data->forks[first_fork]), 0);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_status(philo, FORK);
	return (1);
}

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
	if (philo->data->dead)
		return ;
	if (!take_forks(philo))
		return ;
	if (philo->data->dead)
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
	if (!check_and_print_sleeping(philo))
		return ;
	ft_usleep(philo->data->time_to_sleep, philo->data);
	if (philo->data->dead)
		return ;
	check_and_print_thinking(philo);
}
