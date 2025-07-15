/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysadeq <aysadeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:48:09 by aysadeq           #+#    #+#             */
/*   Updated: 2025/07/15 17:05:40 by aysadeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

/* ************************************************************************** */
/*                                MACROS                                      */
/* ************************************************************************** */

# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define FORK		"has taken a fork"
# define DIED		"died"

/* ************************************************************************** */
/*                              STRUCTURES                                    */
/* ************************************************************************** */

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;

	int				dead;
	int				finished;
	long long		start_time;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	pthread_mutex_t	dead_lock;

	t_philo			*philos;

}	t_data;

struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	t_data			*data;
};

/* ************************************************************************** */
/*                            FUNCTION PROTOTYPES                             */
/* ************************************************************************** */

//--------------- parsing arguments -------------//
int			parse_args(int argc, char **argv, t_data *data);
int			ft_atoi(const char *str);
int			is_valid_number(char *str);

//--------------- initialization -------------//
int			init_data(t_data *data);
int			init_philos(t_data *data);

//--------------- utilities -------------//
long long	get_time(void);
void		ft_usleep(long long time, t_data *data);
void		print_status(t_philo *philo, char *status);

//--------------- philosopher actions -------------//
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);

//--------------- philosopher forks -------------//
int			take_forks(t_philo *philo);

//--------------- checks -------------//
int			check_and_print_sleeping(t_philo *philo);
void		check_and_print_thinking(t_philo *philo);

//--------------- simulation -------------//
int			start_simulation(t_data *data);
void		*monitor(void *arg);

//--------------- cleanup -------------//
void		cleanup(t_data *data);

#endif