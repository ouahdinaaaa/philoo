/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:10:57 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/08 19:58:34 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	s = malloc(count * size);
	if (!s)
		return (NULL);
	while (i < count * size)
	{
		s[i] = '\0';
		i++;
	}
	return (s);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	num;
	char	*str;

	str = (char *)nptr;
	sign = 1;
	num = 0;
	while ((*str == ' ') || (*str == '\t') || (*str == '\n')
		|| (*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str + 1 == '-' || *str + 1 == '+')
		return (0);
	else if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}

t_mutex	*init_mutex(char **argv)
{
	t_mutex	*mutex;

	mutex = ft_calloc(sizeof(t_mutex), 1);
	if (!mutex)
		return (NULL);
	mutex->fork = ft_calloc(sizeof(pthread_mutex_t), ft_atoi(argv[1]));
	if (!mutex->fork)
		return (NULL);
	pthread_mutex_init(&mutex->print, NULL);
	pthread_mutex_init(&mutex->lock, NULL);
	pthread_mutex_init(&mutex->death, NULL);
	pthread_mutex_init(&mutex->meal, NULL);
	mutex->die = 0;
	mutex->time = 0;
	mutex->end = 0;
	return (mutex);
}

t_philo	*create_philo(int argc, char **argv, t_philo *philo, t_mutex *mutex)
{
	int	position;

	position = 0;
	while (position < ft_atoi(argv[1]))
	{
		philo[position].position = position;
		philo[position].nbr_philo = ft_atoi(argv[1]);
		philo[position].time_to_die = ft_atoi(argv[2]);
		philo[position].time_to_eat = ft_atoi(argv[3]);
		philo[position].time_to_sleep = ft_atoi(argv[4]);
		philo[position].last_eat = 0;
		philo[position].nbr_tours = 0;
		if (argc == 6)
			philo[position].nbr_eat = ft_atoi(argv[5]);
		else
			philo[position].nbr_eat = -1;
		philo[position].mutex = mutex;
		pthread_mutex_init(&philo[position].eat, NULL);
		pthread_mutex_init(&philo[position].mutex->fork[position], NULL);
		position++;
	}
	return (philo);
}

t_philo	*init_philo(int argc, char **argv, t_mutex *mutex)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (NULL);
	philo = create_philo(argc, argv, philo, mutex);
	// set_nbr_tour(philo, 0);
	return (philo);
}
