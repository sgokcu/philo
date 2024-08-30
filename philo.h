#ifndef PHILO_H
#define PHILO_H
#define ALIVE 1
#define DEAD 0

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int pn;
	int status;
	int eat_count;
	int last_eat;
	int l_fork;
	int r_fork;
	struct s_hold *hold;
	pthread_t thread;
}	t_philosopher;

typedef struct s_hold
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				eat_count;
	struct timeval	time_val;
	long 			start_time;
	struct timeval	time_val;
	pthread_mutex_t	eat_mutex;
	t_philosopher	*philosopher;
	pthread_mutex_t	*fork;
}	t_hold;

int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_arg_check(char **av);
int		my_exit(t_hold *hold);
void 	*version(void *p);
void 	placing(t_hold *hold, int ac, char **av);
long	time_milisecond(t_hold	*hold);
void	my_printf(t_philosopher *philosopher, char	*msg);
void	p_check(t_philosopher *p);
void	ft_sleep(t_philosopher *p, long time);




#endif