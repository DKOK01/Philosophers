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

/* Shared program data structure */
typedef struct s_data
{
    /* Program arguments */
    int				num_philos;		/* Number of philosophers */
    int				time_to_die;	/* Time to die (ms) */
    int				time_to_eat;	/* Time to eat (ms) */
    int				time_to_sleep;	/* Time to sleep (ms) */
    int				must_eat;		/* Required meals (-1 if not set) */
    
    /* Program state */
    int				dead;			/* Death flag (0 = alive, 1 = dead) */
    int				finished;		/* All ate enough flag */
    long long		start_time;		/* Program start timestamp */
    
    /* Synchronization */
    pthread_mutex_t	*forks;			/* Array of fork mutexes */
    pthread_mutex_t	print;			/* Print mutex */
    pthread_mutex_t	meal;			/* Meal checking mutex */
    pthread_mutex_t	dead_lock;		/* Death flag mutex */
    
    /* Philosophers array */
    t_philo			*philos;		/* Array of philosophers */
}   t_data;



/* Individual philosopher structure */
typedef struct s_philo
{
	int				id;				/* Philosopher ID (1 to n) */
	int				meals_eaten;	/* Number of meals eaten */
	long long		last_meal;		/* Timestamp of last meal */
	int				left_fork;		/* Left fork index */
	int				right_fork;		/* Right fork index */
	pthread_t		thread;			/* Philosopher thread */
	t_data			*data;			/* Pointer to shared data */
}	t_philo;


/* ************************************************************************** */
/*                            FUNCTION PROTOTYPES                             */
/* ************************************************************************** */

/* Parsing and validation */
int			parse_args(int argc, char **argv, t_data *data);
int			ft_atoi(const char *str);
int			is_valid_number(char *str);

/* Initialization */
int			init_data(t_data *data);
int			init_philos(t_data *data);
int			init_mutexes(t_data *data);

/* Utils */
long long	get_time(void);
void		ft_usleep(long long time, t_data *data);
void		print_status(t_philo *philo, char *status);

/* Actions */
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);
int			take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

/* Threads */
int			start_simulation(t_data *data);
void		*philosopher(void *arg);
void		*monitor(void *arg);

/* Checks */
int			is_dead(t_philo *philo);
int			all_ate_enough(t_data *data);

/* Cleanup */
void		cleanup(t_data *data);
void		destroy_mutexes(t_data *data);

#endif