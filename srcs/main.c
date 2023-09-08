/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:18:17 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/08 19:58:28 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/philo.h"

void	philo_solo(char **argv)
{
	printf("%-10i 1   has taken a fork\n", ft_atoi(argv[2]) - ft_atoi(argv[2]));
	usleep(ft_atoi(argv[2]) * 1000);
	printf("%-10i 1   died\n", ft_atoi(argv[2]));
}

void	free_thread(t_philo *philo, t_mutex *mutex)
{
	// int	i;
	// int	size;

	// size = philo[0].nbr_philo;
	// i = -1;
	// while (i < size)
	// {
	// 	pthread_detach(philo[i].philo);
	// 	i++;
	// }
	free(philo->mutex->fork);
	free(mutex);
	free(philo);
	// (void)mutex;
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_mutex	*mutex;

	if (check_arg(argc, argv))
		return (1);
	mutex = init_mutex(argv);
	philo = init_philo(argc, argv, mutex);
	if (ft_atoi(argv[1]) == 1)
		return (philo_solo(argv), 1);
	create_thread(philo);
	// free_thread(philo, mutex);
	return (0);
}
