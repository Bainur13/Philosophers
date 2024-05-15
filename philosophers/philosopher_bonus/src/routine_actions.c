/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:48:15 by druina            #+#    #+#             */
/*   Updated: 2024/05/14 18:05:18 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	sem_wait(philo->program->dead_lock);
	if (philo->dead == 1)
	{
		sem_post(philo->program->dead_lock);
		return (1);
	}
	sem_post(philo->program->dead_lock);
	return (0);
}

void	print_message(char *str, t_philo *philo, int id, int dead_lock)
{
	size_t	time;

	if (philo->stop == 1)
		return ;
	sem_wait(philo->program->write_lock);
	time = get_current_time() - philo->program->start_time;
	printf("%ld %d %s\n", time, id, str);
	sem_post(philo->program->write_lock);
}

void	think(t_philo *philo)
{
	if (philo->stop == 1)
		return ;
	print_message("is thinking", philo, philo->id, 0);
}

void	dream(t_philo *philo)
{
	if (philo->stop == 1)
		return ;
	print_message("is sleeping", philo, philo->id, 0);
	ft_usleep(philo->program->ttsleep);
}

void	eat(t_philo *philo)
{
	if (philo->stop == 1)
		return ;
	sem_wait(philo->program->forks);
	print_message("has taken a fork", philo, philo->id, 0);
	sem_wait(philo->program->forks);
	print_message("has taken a fork", philo, philo->id, 0);
	philo->last_meal = get_current_time();
	print_message("is eating", philo, philo->id, 0);
	ft_usleep(philo->program->tteat);
	sem_post(philo->program->forks);
	sem_post(philo->program->forks);
	philo->meal_count++;
}
