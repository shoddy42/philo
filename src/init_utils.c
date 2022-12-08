/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 14:50:47 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/08 17:48:12 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	init_error(char *error_msg)
{
	printf("%s\n", error_msg);
	return (EXIT_FAILURE);
}

/**
 * @brief 
 * 
 * @param ac ac from main.
 * @param av av from main.
 * @return 0 if input is legal. init_error else. 
 */
bool	legal_input(int ac, char **av)
{
	int	i;
	int	x;

	i = 0;
	if (ac < 5)
		return (init_error("Usage ./philo <NB_PHILOS> <TT_DIE> \
<TT_EAT> <TT_SLEEP> optional: <NB_MEALS>"));
	if (ac > 6)
		return (init_error("Too many arguments."));
	while (av[++i])
	{
		x = -1;
		while (av[i][++x])
			if ((av[i][x] < '0' || av[i][x] > '9'))
				return (init_error("Only numeric arguments allowed."));
	}
	return (0);
}

bool	create_threads(t_deep *thoughts)
{
	int		i;
	t_phil	*philo;

	i = -1;
	philo = thoughts->philos;
	while (++i < thoughts->variables[NB_PHILOS])
		if (pthread_create(&philo[i].thread, NULL,
				life, (void *)&philo[i]) != 0)
			return (init_error("Failed to create thread."));
	if (pthread_create(&thoughts->shakespeare,
			NULL, &shakespeare, thoughts) != 0)
		return (init_error("Failed to create shakespeare."));
	return (0);
}

bool	join_threads(t_deep *thoughts)
{
	int		i;
	t_phil	*philo;

	i = -1;
	philo = thoughts->philos;
	while (++i < thoughts->variables[NB_PHILOS])
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (init_error("Failed to join thread!"));
	if (pthread_join(thoughts->shakespeare, NULL) != 0)
		return (init_error("Failed to join shakespeare."));
	return (0);
}

bool	destroy_forks(t_deep *thoughts)
{
	int		i;
	t_phil	*philo;

	i = -1;
	philo = thoughts->philos;
	while (++i < thoughts->variables[NB_PHILOS])
	{
		pthread_mutex_destroy(thoughts->philos->right);
		pthread_mutex_destroy(&thoughts->philos->soul);
	}
	pthread_mutex_destroy(&thoughts->writers_block);
	pthread_mutex_destroy(&thoughts->sync);
	return (0);
}
