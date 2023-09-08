/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:53:45 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/08 19:58:22 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/philo.h"

void	create_thread(t_philo *philo)
{
	int	i;
	long	time;

	i = 0;
	time = timestamp();
	philo->mutex->start = time;
	while (i < philo[0].nbr_philo)
	{
		philo[i].last_eat = philo[i].mutex->start;
		// pthread_mutex_lock(&philo[i].eat);
		pthread_create(&philo[i].philo, NULL, &routine, &philo[i]);
		// pthread_mutex_unlock(&philo[i].eat);
		i++;
	}
	i = 0;
	while (i < philo[0].nbr_philo)
	{
		pthread_mutex_lock(&philo[i].mutex->death);
		if (philo[i].mutex->die == 1)
		{
			pthread_mutex_unlock(&philo[i].mutex->death);
			pthread_join(philo[i].philo, NULL);
			return ;
		}
		pthread_mutex_unlock(&philo[i].mutex->death);
		pthread_join(philo[i].philo, NULL);
		i++;
	}
}
