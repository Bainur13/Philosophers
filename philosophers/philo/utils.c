/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:03:47 by udumas            #+#    #+#             */
/*   Updated: 2024/08/16 19:04:54 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	only_digit(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_right_time(char *msg, t_philosopher *philo)
{
	long	time;

	pthread_mutex_lock(philo->start_lock);
	time = get_time() - philo->start_time;
	pthread_mutex_unlock(philo->start_lock);
	if (!dead_o_not_dead(philo))
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%ld %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(philo->write_lock);
	}
}

int	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
int	ft_atoi(const char *str)
{
	int		i;
	int		isneg;
	long	res;

	i = 0;
	isneg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isneg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * isneg);
}
