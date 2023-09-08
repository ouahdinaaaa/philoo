/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 10:50:53 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/08 19:58:00 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->fork[philo->position]);
	print_action(philo, philo->position, "has taken a fork");
	if (philo->position == philo->nbr_philo)
	{
		pthread_mutex_lock(&philo->mutex->fork[0]);
		print_action(philo, philo->position, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->mutex->fork[philo->position + 1]);
		print_action(philo, philo->position, "has taken a fork");
	}
}

void	put_fork(t_philo *philo)
{
	if (philo->position == philo->nbr_philo)
	{
		pthread_mutex_unlock(&philo->mutex->fork[philo->position]);
		pthread_mutex_unlock(&philo->mutex->fork[0]);
	}
	else
	{
		pthread_mutex_unlock(&philo->mutex->fork[philo->position]);
		pthread_mutex_unlock(&philo->mutex->fork[philo->position + 1]);
	}
}

int	is_philo_dead(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->eat);
	time = timestamp() - philo->last_eat;
	pthread_mutex_unlock(&philo->eat);
	pthread_mutex_lock(&philo->eat);
	if (philo->last_eat && time > philo->time_to_die)
	{
		pthread_mutex_unlock(&philo->eat);
		pthread_mutex_lock(&philo->mutex->death);
		philo->mutex->die = 1;
		print_action(philo, philo->position, "died");
		pthread_mutex_unlock(&philo->mutex->death);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->eat);
	return (0);
}
