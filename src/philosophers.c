/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 09:12:20 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/08 18:35:21 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	confirm_reality(t_deep *thoughts)
{
	bool	existance;

	pthread_mutex_lock(&thoughts->sync);
	existance = (!thoughts->oblivion);
	pthread_mutex_unlock(&thoughts->sync);
	return (existance);
}

static void	consume(t_phil *philo)
{
	t_deep			*thoughts;
	unsigned long	time;

	thoughts = philo->thoughts;
	pthread_mutex_lock(philo->right);
	add_queue(get_time() - thoughts->epoch, FORK, philo->id, thoughts);
	pthread_mutex_lock(philo->left);
	add_queue(get_time() - thoughts->epoch, FORK2, philo->id, thoughts);
	pthread_mutex_lock(&philo->soul);
	time = get_time();
	add_queue(time - thoughts->epoch, EAT, philo->id, thoughts);
	philo->last_supper = time;
	pthread_mutex_unlock(&philo->soul);
	better_sleep(philo->thoughts->variables[TT_EAT]);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_lock(&philo->soul);
	philo->meals++;
	pthread_mutex_unlock(&philo->soul);
}

static void	prep_life(t_deep *thoughts, t_phil *philo)
{
	pthread_mutex_lock(&thoughts->sync);
	pthread_mutex_unlock(&thoughts->sync);
	philo->last_supper = thoughts->epoch;
	if (philo->id % 2 == 0)
		usleep(200);
}

void	*life(void *param)
{
	t_phil	*philo;
	t_deep	*thoughts;
	t_state	state;
	bool	existance;

	philo = param;
	thoughts = philo->thoughts;
	existance = true;
	state = THINKING;
	prep_life(thoughts, philo);
	while (existance)
	{
		if (state == THINKING)
			add_queue(get_time() - thoughts->epoch, THINK, philo->id, thoughts);
		if (state == EATING)
			consume(philo);
		else if (state == SLEEPING)
		{
			add_queue(get_time() - thoughts->epoch, SLEEP, philo->id, thoughts);
			better_sleep(philo->thoughts->variables[TT_SLEEP]);
		}
		state = (state + 1) % STATES;
		existance = confirm_reality(thoughts);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_deep	*thoughts;

	thoughts = ft_calloc(1, sizeof(t_deep));
	if (!thoughts)
		return (init_error("FAILED LMAO\n"));
	if (init_philosophers(ac, av, thoughts) != 0)
		return (init_error("Failed to init_philosophers"));
	if (create_threads(thoughts) != 0)
		return (EXIT_FAILURE);
	thoughts->epoch = get_time();
	pthread_mutex_unlock(&thoughts->sync);
	watch_threads(thoughts);
	join_threads(thoughts);
	destroy_forks(thoughts);
	return (0);
}
