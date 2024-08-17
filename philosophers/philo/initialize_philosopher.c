/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosopher.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:58:32 by udumas            #+#    #+#             */
/*   Updated: 2024/05/11 16:59:21 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	setup_information(int ac, char **av)
{
	int	nphilo;
	int	ttdie;
	int	tteat;
	int	ttsleep;
	int	ntimes;

	if (!only_digit(av + 1))
		return (printf("Error: wrong arguments\n"), -1);
	nphilo = ft_atoi(av[1]);
	ttdie = ft_atoi(av[2]);
	tteat = ft_atoi(av[3]);
	ttsleep = ft_atoi(av[4]);
	if (ac == 6)
		ntimes = ft_atoi(av[5]);
	else
		ntimes = -1;
	if (nphilo < 1 || ttdie < 60 || tteat < 60 || ttsleep < 60 || (ac == 6
			&& ntimes < 1))
		return (printf("Error: wrong arguments\n"), -1);
	if (ttdie > INT_MAX || tteat > INT_MAX || ttsleep > INT_MAX)
		return (printf("Error: arguments to big\n"), -1);
	return (0);
}

void	init_mutex(t_data *data, pthread_mutex_t forks[200], char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->start_lock, NULL);
}

void	add_informations(t_philosopher *philo, char **av, int ac)
{
	philo->eaten = 0;
	philo->eating = 0;
	philo->nphilo = ft_atoi(av[1]);
	philo->ttdie = ft_atoi(av[2]);
	philo->tteat = ft_atoi(av[3]);
	philo->ttsleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->ntimes = ft_atoi(av[5]);
	else
		philo->ntimes = -1;
}

void	initialize_philosophers(t_data *data, pthread_mutex_t forks[200],
		char **av, int ac)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philosopher) * ft_atoi(av[1]));
	data->dead_signal = 0;
	data->start_signal = 0;
	if (!data->philosophers)
	{
		printf("Error: malloc failed\n");
		return ;
	}
	while (data->philosophers && i < ft_atoi(av[1]))
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].start_time = get_time();
		data->philosophers[i].last_meal = get_time();
		data->philosophers[i].dead = &(data->dead_signal);
		data->philosophers[i].start = &(data->start_signal);
		data->philosophers[i].r_fork = &forks[i];
		data->philosophers[i].l_fork = &forks[(i + 1) % ft_atoi(av[1])];
		data->philosophers[i].write_lock = &data->write_lock;
		data->philosophers[i].dead_lock = &data->dead_lock;
		data->philosophers[i].meal_lock = &data->meal_lock;
		data->philosophers[i].start_lock = &data->start_lock;
		add_informations(&data->philosophers[i], av, ac);
		i++;
	}
}
