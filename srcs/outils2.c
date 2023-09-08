/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:04:50 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/08 19:58:38 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/philo.h"

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
	{
		printf("Error of numbers to arguments.\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Invalid argument : is not a valid number: %s\n", argv[i]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	print_action(t_philo *philo, int num_philo, char *action)
{
	pthread_mutex_lock(&philo->mutex->print);
	printf("%-10li %i %s\n", timestamp() - philo->mutex->start, num_philo + 1, action);
	pthread_mutex_unlock(&philo->mutex->print);
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo, philo->position, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_action(philo, philo->position, "is thinking");
}

void	eat(t_philo *philo)
{
	take_fork(philo);
	print_action(philo, philo->position, "is eating");
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&philo->eat);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->eat);
	pthread_mutex_lock(&philo->mutex->lock);
	philo->nbr_tours++;
	pthread_mutex_unlock(&philo->mutex->lock);
	put_fork(philo);
}
