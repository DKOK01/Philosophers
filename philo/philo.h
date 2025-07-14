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

typedef struct s_philo t_philo;

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

}   t_data;

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

int			parse_args(int argc, char **argv, t_data *data);
int			ft_atoi(const char *str);
int			is_valid_number(char *str);

int			init_data(t_data *data);
int			init_philos(t_data *data);

long long	get_time(void);
void		ft_usleep(long long time, t_data *data);
void		print_status(t_philo *philo, char *status);

void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);

int			start_simulation(t_data *data);
void		*monitor(void *arg);

void		cleanup(t_data *data);


#endif