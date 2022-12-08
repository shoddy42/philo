/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 09:12:24 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/08 17:56:55 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include "print.h"
// # include <fcntl.h> // DBG

typedef struct s_deepthought	t_deep;
typedef pthread_mutex_t			t_mutex;

# define STATES 3
/**
 * @brief The three state types a philosopher can be in.
 */
typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
}	t_state;

/**
 * @brief The main philosopher struct.
 * 
 * @param thread	The thread that represents the philosopher.
 * @param right		The right fork (mutex) is the philosophers own fork.
 * @param left		The left fork (mutex) is the left neighbor's fork.
 * @param soul		This mutex is what prevents dataraces within the philo
 * @param last_supper	The last time a philosopher ate.
 * @param meals			The amount of meals the philosopher has consumed.
 * @param id			The philosopher's ID (number that represents them)
 * @param thoughts		A pointer to the main t_deep *thoughts struct.
 */
typedef struct s_philosopher
{
	pthread_t		thread;
	t_mutex			*right;
	t_mutex			*left;
	t_mutex			soul;

	unsigned long	last_supper;
	int				meals;
	int				id;
	t_deep			*thoughts;
}	t_phil;

/** 
 * @brief	Enumerators for clarity when accessing the simulations variables.
 *
 * @param	NB_PHILOS	The amount of philosophers in the simulation.
 * @param	TT_DIE		The time (in ms?) it takes for a philosopher to die.
 * @param	TT_EAT		The time (in ms?) it takes for a philosopher to eat.
 * @param	TT_SLEEP 	The time (in ms?) it takes for a philosopher to sleep.
 * @param	NB_MEALS 	The number of times the philosophers will eat
 * 					 	before ending the simulation.
 */
enum e_variables
{
	NB_PHILOS,
	TT_DIE,
	TT_EAT,
	TT_SLEEP,
	NB_MEALS,
};

/**
 * @brief The main program data for philosophers
 * @param philos	Has pointers to all philosophers in the simulation.
 * @param shakespeare The writing thread.
 * @param writers_block The mutex protecting shakespeare.
 * @param log	t_log struct containing all that shakespeare needs to write.
 * @param ------
 * @param sync		Mutex to assure synchronised start.
 * @param epoch		The starting time of the simulation.
 * @param satisfied	The amount of philosophers that have eaten enough.
 * @param oblivion	Turns true when simulation ends.
 * @param variables[5] Contains variables that affect the simulation,
 * 		 			 defined by e_variables
 */
typedef struct s_deepthought
{
	t_phil			*philos;
	unsigned long	epoch;
	t_mutex			sync;

	pthread_t		shakespeare;
	t_mutex			writers_block;
	t_log			*log;

	long			variables[5];
	int				satisfied;
	bool			oblivion;
	int				fd;
}	t_deep;

// philosophers.c
bool			confirm_reality(t_deep *thoughts);
void			*life(void *param);

// utils.c
void			better_sleep(unsigned long duration);
unsigned long	get_time(void);
void			*ft_calloc(size_t count, size_t size);
long			ft_atol(const char *nb);

// init.c
bool			init_deepthought(int ac, char **av, t_deep *thoughts);
bool			init_time(t_deep *thoughts);
bool			init_philosophers(int ac, char **av, t_deep *thoughts);
bool			init_log(t_deep *thoughts);

// gods.c
void			*watch_threads(t_deep *thoughts);
void			end_universe(t_deep *thoughts);

// poet.c
void			*shakespeare(void *param);
void			add_queue(unsigned long time, t_msg_type type, \
					int id, t_deep *thoughts);

// init_utils.c
bool			init_error(char *error_msg);
bool			legal_input(int ac, char **av);
bool			create_threads(t_deep *thoughts);
bool			join_threads(t_deep *thoughts);
bool			destroy_forks(t_deep *thoughts);

// fancy.c
const char		*random_food(t_log *log);
void			init_fancy(t_log *log);

#endif