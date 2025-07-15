/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:00:46 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/15 17:10:35 by aysadeq          ###   ########.fr       */
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

static void	get_fork_order_odd(t_philo *philo, int *first, int *second)
{
	if (philo->id == philo->data->num_philos)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

static void	get_fork_order_even(t_philo *philo, int *first, int *second)
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
	if (philo->data->num_philos % 2 == 1)
		get_fork_order_odd(philo, &first_fork, &second_fork);
	else
		get_fork_order_even(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, FORK);
	if (philo->data->dead)
		return (pthread_mutex_unlock(&philo->data->forks[first_fork]), 0);
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_status(philo, FORK);
	return (1);
}
