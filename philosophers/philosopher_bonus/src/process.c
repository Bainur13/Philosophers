/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:01:57 by druina            #+#    #+#             */
/*   Updated: 2024/05/14 19:08:18 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->stop)
	{
		usleep(100);
		if (get_current_time() - philo->last_meal > philo->program->ttdie)
		{
			philo->dead = 1;
			sem_wait(philo->program->write_lock);
			printf("%lld %d %s\n", \
					get_current_time() - philo->program->start_time, philo->id, "died");
			philo->stop = 1;
			break ;
		}
		if (philo->program->ntimes != -1 && philo->meal_count >= philo->program->ntimes)
		{
			philo->stop = 1;
			break ;
		}
	}
	if (philo->dead)
	{
		destroy_all(&philo);
		exit (1);
	}
	else
	{
		destroy_all(&philo);
		exit (0);
	}
}
int	not_dead_o_full(t_philo *philo)
{
	sem_wait(philo->program->dead_lock);
	if (philo->dead == 1)
	{
		sem_post(philo->program->dead_lock);
		exit(-1);
	}
	sem_post(philo->program->dead_lock);
	sem_wait(philo->program->meal_lock);
	if (philo->program->ntimes != -1
		&& philo->meal_count >= philo->program->ntimes)
	{
		sem_post(philo->program->meal_lock);
		exit(0);
	}
	sem_post(philo->program->meal_lock);
	return (1);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, check_monitor, philo);
	pthread_detach(thread);
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
}

void	ft_create_process(t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	philo->pid = (int *)malloc(sizeof(int) * philo->program->nphilos);
	while (i < philo->program->nphilos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == 0)
		{		
			philo->id = i + 1;
			philo_routine(philo);
		}
		i++;
	}
}
