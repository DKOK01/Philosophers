/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:00:46 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/17 12:49:21 by aysadeq          ###   ########.fr       */
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

static void	get_fork_order(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
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
	get_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, FORK);
	if (is_simulation_over(philo->data))
		return (pthread_mutex_unlock(&philo->data->forks[first_fork]), 0);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_status(philo, FORK);
	return (1);
}
