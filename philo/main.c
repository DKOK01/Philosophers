/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:52:07 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/11 09:59:36 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(const char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

int	parse_args(int argc, char **argv, t_data *data)
{
	int	i;
	int	value;

	if (argc != 5 && argc != 6)
		return (printf("Error: Wrong number of arguments\n"), 0);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (printf("Error: Invalid number format: '%s'\n", argv[i]), 0);
		value = ft_atoi(argv[i]);
		if (value <= 0)
			return (printf("Error: Argument %d must be positive\n", i), 0);
		i++;
	}
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_args(argc, argv, &data))
		return (1);
	// if (!init_data(&data))
	// 	return (printf("Error: Failed to initialize program data\n"), 1);
	// if (!init_philos(&data))
	// {
	// 	cleanup(&data);
	// 	return (printf("Error: Failed to initialize philosophers\n"), 1);
	// }
	// if (!start_simulation(&data))
	// {
	// 	cleanup(&data);
	// 	return (printf("Error: Failed to start simulation\n"), 1);
	// }
	// cleanup(&data);
	return (0);
}


