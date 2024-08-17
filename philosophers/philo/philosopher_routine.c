/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:42:58 by udumas            #+#    #+#             */
/*   Updated: 2024/08/16 19:26:05 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	which_fork(t_philosopher *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_right_time("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		print_right_time("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_right_time("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		print_right_time("has taken a fork", philo);
	}
}

void	which_fork_release(t_philosopher *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	make_philo_eat(t_philosopher *philo)
{
	if (philo->nphilo == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_right_time("has taken a fork", philo);
		ft_usleep(philo->ttdie);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	philo->eating = 1;
	print_right_time("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->tteat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	make_philo_sleep_o_think(t_philosopher *philo, int status)
{
	if (status == 0)
	{
		ft_usleep(philo->ttsleep);
		print_right_time("is sleeping", philo);
	}
	else
		print_right_time("is thinking", philo);
}

void	*philosopher_routine(void *philo_void)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philo_void;
	while (1)
	{
		pthread_mutex_lock(philo->start_lock);	
		if (*(philo->start) == 1)
		{
			pthread_mutex_unlock(philo->start_lock);
			break;
		}	
		pthread_mutex_unlock(philo->start_lock);
	}
	pthread_mutex_lock(philo->start_lock);
	philo->start_time = get_time();
	pthread_mutex_unlock(philo->start_lock);
	if (philo->id % 2 == 0)
		usleep(10);
	while (dead_o_not_dead(philo) == 0)
	{
		make_philo_eat(philo);
		make_philo_sleep_o_think(philo, 0);
		make_philo_sleep_o_think(philo, 1);
	}
	return ((void *)philo);
}
