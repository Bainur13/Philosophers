/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:25:51 by udumas            #+#    #+#             */
/*   Updated: 2024/05/11 18:16:23 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_philosopher
{
	pthread_t		thread;

	int				id;
	long			start_time;
	long			last_meal;
	int				eaten;
	int				eating;
	int				*dead;

	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;

	int				nphilo;
	long			ttdie;
	long			tteat;
	long			ttsleep;
	long			ntimes;
}					t_philosopher;

typedef struct s_data
{
	int				dead_signal;

	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;

	t_philosopher	*philosophers;
}					t_data;

//### INITIALIZE ###//

int					setup_information(int ac, char **av);
void				initialize_philosophers(t_data *data,
						pthread_mutex_t forks[200], char **av, int ac);
void				init_mutex(t_data *data, pthread_mutex_t *forks, char **av);

//### START_THREAD ###//

void				start_threads(t_data *data);

//### THREADS ROUTINES ###//

void				*philosopher_routine(void *philo_void);
int					dead_o_not_dead(t_philosopher *philo);

//### ARBITRATOR ROUTINE ###//

void				*arbitrator_routine(void *arg);
int					check_every1_eaten(t_philosopher *philo);

//### UTILS ###//

void				print_right_time(char *msg, t_philosopher *philo);
int					only_digit(char **av);
long long			get_time(void);
int					ft_usleep(size_t milliseconds);
int					ft_atoi(const char *str);
//### END OF HEADER ###//

#endif
