/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:25:27 by udumas            #+#    #+#             */
/*   Updated: 2024/05/11 16:57:25 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	bulldozer(t_data *data, pthread_mutex_t *forks)
{
	int	nphilo;
	int	i;

	i = 0;
	if (!forks)
		return ;
	nphilo = data->philosophers[0].nphilo;
	while (i < nphilo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	if (!data->philosophers)
		return (free(data));
	free(data->philosophers);
	free(data);
	return ;
}

int	main(int ac, char **av)
{
	t_data			*data;
	pthread_mutex_t	forks[200];

	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	if (setup_information(ac, av) == -1)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	init_mutex(data, forks, av);
	initialize_philosophers(data, forks, av, ac);
	start_threads(data);
	bulldozer(data, forks);
	return (0);
}
