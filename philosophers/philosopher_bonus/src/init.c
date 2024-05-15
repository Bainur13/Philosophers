/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:05:40 by druina            #+#    #+#             */
/*   Updated: 2024/05/14 18:48:38 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_program *program, char **av)
{
	program->ttdie = ft_atoi(av[2]);
	program->tteat = ft_atoi(av[3]);
	program->ttsleep = ft_atoi(av[4]);
	program->nphilos = ft_atoi(av[1]);
	if (av[5])
		program->ntimes = ft_atoi(av[5]);
	else
		program->ntimes = -1;
}

void	init_semaphore(t_program *program)
{
	sem_unlink("dead_lock");
	sem_unlink("meal_lock");
	sem_unlink("write_lock");
	sem_unlink("forks");
	sem_unlink("dead");
	program->dead_lock = sem_open("dead_lock", O_CREAT, 0644, 1);
	program->meal_lock = sem_open("meal_lock", O_CREAT, 0644, 1);
	program->write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
	program->forks = sem_open("forks", O_CREAT, 0644, program->nphilos);
}

t_philo	*init_program(t_program *program, char **av)
{
	t_philo	*philo;
	int		i;

	init_input(program, av);
	init_semaphore(program);
	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->program = program;
	philo->dead = 0;
	philo->eating = 0;
	philo->stop = 0;
	philo->last_meal = get_current_time();
	if (program->ntimes != -1)
		philo->meal_count = 0;
	else
		philo->meal_count = -1;
	return (philo);
}
