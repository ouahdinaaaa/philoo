/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:01:14 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/08 19:58:42 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/philo.h"

long	timestamp(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

int	get_nbr_tour(t_philo *philo)
{
	int	valeur;

	pthread_mutex_lock(&philo->mutex->lock);
	valeur = philo->nbr_tours;
	pthread_mutex_unlock(&philo->mutex->lock);
	return (valeur);
}

void	set_nbr_tour(t_philo *philo, int valeur)
{
	pthread_mutex_lock(&philo->mutex->lock);
	philo->nbr_tours = valeur;
	pthread_mutex_unlock(&philo->mutex->lock);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->position % 2 != 0)
		usleep((philo->time_to_eat - 5) * 1000);
	if (philo->nbr_eat != -1)
	{
		while (philo->nbr_tours != philo->nbr_eat)
		{
			routine2(philo);
			pthread_mutex_lock(&philo->mutex->meal);
			if (philo->mutex->end == philo->nbr_eat)
			{
				pthread_mutex_unlock(&philo->mutex->meal);
				pthread_mutex_lock(&philo->mutex->death);
				philo->mutex->die = 1;
				pthread_mutex_unlock(&philo->mutex->death);
				break ;
			}
			pthread_mutex_unlock(&philo->mutex->meal);
			sleep_philo(philo);
			think(philo);
		}
	}
	else
	{
		while (!is_philo_dead(philo))
		{
			routine2(philo);
			pthread_mutex_lock(&philo->mutex->meal);
			if (philo->mutex->end == philo->nbr_eat)
			{
				pthread_mutex_unlock(&philo->mutex->meal);
				pthread_mutex_lock(&philo->mutex->death);
				philo->mutex->die = 1;
				pthread_mutex_unlock(&philo->mutex->death);
				break ;
			}
			pthread_mutex_unlock(&philo->mutex->meal);
			sleep_philo(philo);
			think(philo);
		}
	}
	return (NULL);
}

void	routine2(t_philo *philo)
{
	eat(philo);
	if (get_nbr_tour(philo) == philo->nbr_philo)
	{
		pthread_mutex_lock(&philo->mutex->meal);
		philo->mutex->end++;
		pthread_mutex_unlock(&philo->mutex->meal);
		set_nbr_tour(philo, 0);
	}
}
