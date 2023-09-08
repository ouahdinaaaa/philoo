/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:49:44 by ayael-ou          #+#    #+#             */
/*   Updated: 2023/09/08 19:58:51 by ayael-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	pthread_mutex_t	death;
	pthread_mutex_t	meal;
	int				end;
	long	start;
	int				die;
	long			time;
}					t_mutex;

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	eat;
	int				position;
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_eat;
	int				nbr_tours;
	t_mutex			*mutex;
	long			temps;
	long			last_eat;
}					t_philo;

void				*ft_calloc(size_t count, size_t size);
int					ft_atoi(const char *nptr);
t_philo				*init_philo(int argc, char **argv, t_mutex *mutex);
t_mutex				*init_mutex(char **argv);
void				create_thread(t_philo *philo);
void				verif_thread(t_philo *philo);
int					is_philo_dead(t_philo *philo);
void				print(t_philo *philo, long int time, char *state);
void				free_all(t_philo *philo, t_mutex *mutex);
int					check_arg(int argc, char **argv);
t_philo				*create_philo(int argc, char **argv,
						t_philo *philo, t_mutex *mutex);
void				free_thread(t_philo *philo, t_mutex *mutex);
void				verif_join(t_philo *philo);
int					get_nbr_tour(t_philo *philo);
long				timestamp(void);
void				set_nbr_tour(t_philo *philo, int valeur);
void				routine2(t_philo *philo);
void				print_action(t_philo *philo, int num_philo, char *action);
void				sleep_philo(t_philo *philo);
void				take_fork(t_philo *philo);
void				put_fork(t_philo *philo);
void				think(t_philo *philo);
void				eat(t_philo *philo);
void				*routine(void *arg);

#endif
