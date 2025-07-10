/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:52:07 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/10 17:44:03 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * validate_ranges - Validate argument value ranges
 * 
 * Checks if parsed values are within acceptable ranges for the simulation.
 * Ensures realistic and safe values for all timing parameters.
 * 
 * @data: Pointer to data structure with parsed values
 * Return: 1 if all values are valid, 0 otherwise
 */
static int	validate_ranges(t_data *data)
{
	if (data->num_philos < 1 || data->num_philos > 200)
	{
		printf("Error: Number of philosophers must be between 1 and 200\n");
		return (0);
	}
	if (data->time_to_die < 60)
	{
		printf("Error: time_to_die must be at least 60ms\n");
		return (0);
	}
	if (data->time_to_eat < 1)
	{
		printf("Error: time_to_eat must be at least 1ms\n");
		return (0);
	}
	if (data->time_to_sleep < 1)
	{
		printf("Error: time_to_sleep must be at least 1ms\n");
		return (0);
	}
	if (data->must_eat != -1 && data->must_eat < 1)
	{
		printf("Error: number_of_times_each_philosopher_must_eat must be at least 1\n");
		return (0);
	}
	return (1);
}

/*
 * parse_args - Parse and validate command line arguments
 * 
 * Validates argument count, format, and ranges for all program parameters.
 * Converts string arguments to integers and stores them in data structure.
 * Handles both mandatory and optional arguments (must_eat).
 * 
 * @argc: Number of command line arguments
 * @argv: Array of command line argument strings
 * @data: Pointer to data structure to fill with parsed values
 * Return: 1 if parsing successful, 0 on error
 */
int	parse_args(int argc, char **argv, t_data *data)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("Error: Invalid number format: '%s'\n", argv[i]);
			return (0);
		}
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
	return (validate_ranges(data));
}

/*
 * main - Program entry point
 * 
 * Main function that orchestrates the entire philosopher simulation.
 * Handles argument parsing, initialization, simulation execution, and cleanup.
 * Provides proper error handling and exit codes.
 * 
 * @argc: Number of command line arguments
 * @argv: Array of command line argument strings
 * Return: 0 on success, 1 on error
 */
int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_args(argc, argv, &data))
		return (1);
	if (!init_data(&data))
	{
		printf("Error: Failed to initialize program data\n");
		return (1);
	}
	if (!init_philos(&data))
	{
		printf("Error: Failed to initialize philosophers\n");
		cleanup(&data);
		return (1);
	}
	if (!start_simulation(&data))
	{
		printf("Error: Failed to start simulation\n");
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}


