/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 08:27:04 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/08 17:53:35 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

//todo: error handling
bool	init_philo(t_deep *thoughts, int i)
{
	t_phil	*philos;

	philos = thoughts->philos;
	thoughts->epoch = get_time();
	while (++i < thoughts->variables[NB_PHILOS])
	{
		philos[i].id = i + 1;
		philos[i].thoughts = thoughts;
		philos[i].right = ft_calloc(1, sizeof(t_mutex));
		philos[i].last_supper = thoughts->epoch;
		if (pthread_mutex_init(philos[i].right, NULL) != 0)
			return (init_error("Failed to init right mutex"));
		if (pthread_mutex_init(&philos[i].soul, NULL) != 0)
			return (init_error("Failed to init philo's soul"));
		if (i > 0)
			philos[i].left = philos[i - 1].right;
	}
	if (i > 1)
		philos[0].left = philos[i - 1].right;
	else
		philos[0].left = NULL;
	return (0);
}

// DBG
// thoughts->fd = open("philosophers.log\n", O_CREAT | O_TRUNC | O_RDWR, 0644);
// dup2(thoughts->fd, STDOUT_FILENO);
bool	init_log(t_deep *thoughts)
{
	t_log	*log;

	thoughts->log = ft_calloc(1, sizeof(t_log));
	if (!thoughts->log)
		return (init_error("Failed to allocate for log"));
	log = thoughts->log;
	log->queue = ft_calloc(thoughts->variables[NB_PHILOS] * 100, sizeof(t_msg));
	log->print = ft_calloc(thoughts->variables[NB_PHILOS] * 100, sizeof(t_msg));
	if (!log->queue || !log->print)
		return (init_error("Failed to allocate for log's queue"));
	log->max = thoughts->variables[NB_PHILOS] * 100;
	if (pthread_mutex_init(&thoughts->writers_block, NULL) != 0)
		return (init_error("Failed to init log's mutex"));
	log->msgs[FORK] = FORK_MSG;
	log->msgs[FORK2] = FORK2_MSG;
	log->msgs[EAT] = EATING_MSG;
	log->msgs[SLEEP] = SLEEPING_MSG;
	log->msgs[THINK] = THINKING_MSG;
	log->msgs[DIE] = DEATH_MSG;
	log->msgs[END] = END_MSG;
	if (FOOD)
		init_fancy(thoughts->log);
	return (0);
}

bool	init_deepthought(int ac, char **av, t_deep *thoughts)
{
	long	*vars;

	if (legal_input(ac, av) != 0)
		return (1);
	vars = thoughts->variables;
	vars[NB_PHILOS] = ft_atol(av[NB_PHILOS + 1]);
	vars[TT_DIE] = ft_atol(av[TT_DIE + 1]);
	vars[TT_EAT] = ft_atol(av[TT_EAT + 1]);
	vars[TT_SLEEP] = ft_atol(av[TT_SLEEP + 1]);
	vars[NB_MEALS] = -1;
	if (ac == 6)
		vars[NB_MEALS] = ft_atol(av[NB_MEALS + 1]);
	if (vars[NB_PHILOS] <= 0 || vars[TT_DIE] <= 0 \
		|| vars[TT_EAT] <= 0 || vars[TT_SLEEP] <= 0)
		return (init_error("Only arguments above 0 allowed!"));
	if (vars[NB_PHILOS] > INT_MAX || vars[TT_DIE] > INT_MAX \
		|| vars[TT_EAT] > INT_MAX || vars[TT_SLEEP] > INT_MAX)
		return (init_error("Only arguments under INT_MAX"));
	return (0);
}

bool	init_philosophers(int ac, char **av, t_deep *thoughts)
{
	if (init_deepthought(ac, av, thoughts) != 0)
		return (EXIT_FAILURE);
	thoughts->philos = ft_calloc(thoughts->variables[NB_PHILOS], \
		sizeof(t_phil));
	if (!thoughts->philos)
		return (init_error("Failed to allocate for philosophers."));
	if (init_philo(thoughts, -1) != 0)
		return (EXIT_FAILURE);
	if (init_log(thoughts) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&thoughts->sync, NULL) != 0)
		return (init_error("Failed to initialise sync mutex"));
	pthread_mutex_lock(&thoughts->sync);
	return (0);
}
