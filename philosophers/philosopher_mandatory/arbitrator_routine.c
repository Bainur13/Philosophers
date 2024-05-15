/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:29:36 by udumas            #+#    #+#             */
/*   Updated: 2024/05/11 17:01:09 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	dead_o_not_dead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	check_death(t_philosopher *philo, long ttdie)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= ttdie && philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_ttdie(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nphilo)
	{
		if (check_death(&philo[i], philo[i].ttdie))
		{
			print_right_time("died", &philo[i]);
			pthread_mutex_lock(philo[0].dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_every1_eaten(t_philosopher *philo)
{
	int	i;
	int	how_much;

	i = 0;
	how_much = 0;
	if (philo[0].ntimes == -1)
		return (0);
	while (i < philo[0].nphilo)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].eaten >= philo[0].ntimes)
			how_much++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (how_much >= philo[0].nphilo)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*arbitrator_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_ttdie(data->philosophers) == 1
			|| check_every1_eaten(data->philosophers) == 1)
			break ;
	}
	return ((void *)data);
}
