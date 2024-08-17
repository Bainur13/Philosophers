/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:23:28 by druina            #+#    #+#             */
/*   Updated: 2024/05/14 18:08:52 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argcontent(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

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

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			*philos;

	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	if (setup_information(ac, av) == -1)
		return (0);
	philos = init_program(&program, av);
	program.start_time = get_current_time();
	ft_create_process(philos);
	destroy_all(&philos);
	return (0);
}
