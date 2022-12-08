/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: wkonings <wkonings@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:03:37 by wkonings      #+#    #+#                 */
/*   Updated: 2022/12/08 17:51:31 by wkonings      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H

# ifdef FANCY
#  define FORMAT_MSG "\1\33[38;5;69m %8li\2\33[38;5;236mms \2\33[0m%3i %s\2\3\n"
#  define FORMAT_EAT "\1\33[38;5;69m %8li\2\33[38;5;236mms \2\33[0m%3i %s\2 %s\2\3\n"
#  define FORK_MSG "\1\33[38;5;117mhas taken fork 1\2\1\33[0m\2\3"
#  define FORK2_MSG "\1\33[38;5;117mhas taken fork 2\2\1\33[0m\2\3"
#  define EATING_MSG "\1\33[38;5;198mis eating\2\1\33[0m\2\3"
#  define SLEEPING_MSG "\1\33[38;5;135mis sleeping\2\1\33[0m\2\3"
#  define THINKING_MSG "\1\33[38;5;27mis thinking\2\1\33[0m\2\3"
#  define DEATH_MSG "\1\33[38;5;196mhas died\2\3"
#  define END_MSG "\1\33[38;5;202mSimulation succesful!\2\3"
#  define FOOD 1
# else
#  define FORMAT_MSG "%8li %i %s\n"
#  define FORMAT_EAT "%8li %i %s %s\n"
#  define FORK_MSG "has taken fork"
#  define FORK2_MSG "has taken fork"
#  define EATING_MSG "is eating"
#  define SLEEPING_MSG "is sleeping"
#  define THINKING_MSG "is thinking"
#  define DEATH_MSG "has died"
#  define END_MSG "Simulation succesful!"
#  define FOOD 0
# endif

typedef enum e_message_types
{
	FORK,
	FORK2,
	EAT,
	SLEEP,
	THINK,
	DIE,
	END
}	t_msg_type;

typedef struct s_message
{
	t_msg_type			type;
	unsigned long		time;
	int					id;
}	t_msg;

typedef struct s_log
{
	const char	*msgs[7];
	t_msg		*queue;
	t_msg		*print;
	int			queue_size;
	int			print_size;
	int			max;

	const char	*foods[69];
	int			food_index;
}	t_log;

# define FOOD_TYPES 40
# ifdef FOOD
#  define SPAGHETTI	"\1\2\33[38;5;196mSpaghetti! 🍝\2\3"
#  define PIZZA		"\1\2\33[38;5;m124Pizza! 🍕\2\3"
#  define PIZZA_PEP "\1\2\33[38;5;160mPeperroni Pizza! 🍕\2\3"
#  define PIZZA_HAW "\1\2\33[38;5;172mHawaii Pizza! 🍕🍍\2\3"
#  define GRAPE		"\1\2\33[38;5;162mGrapes! 🍇\2\3"
#  define APPLE		"\1\2\33[38;5;196man apple! 🍎\2\3"
#  define IC_CHOC	"\1\2\33[38;5;130mchocolate icecream! 🍫🍧\2\3"
#  define IC_VAN	"\1\2\33[38;5;15mvanilla icecream! 🍦\2\3"
#  define IC_COODOU "\1\2\33[38;5;173mcookiedough icecream! 🍪🍧\2\3"
#  define IC_STRAW	"\1\2\33[38;5;13mstrawberry cheesecake icecream! 🍓🍧\2\3"
#  define IC_BANANA "\1\2\33[38;5;220mbanana icecream! 🍌🍧\2\3"
#  define IC_RASP	"\1\2\33[38;5;197mraspberry icecream! 🍧\2\3"
#  define BENTO		"\1\2\33[38;5;12mBento! 🍱\2\3"
#  define BURRITO	"\1\2\33[38;5;208mBurritos! 🌯\2\3"
#  define TACO		"\1\2\33[38;5;226mTacos! 🌮\2\3"
#  define FALAFEL	"\1\2\33[38;5;158mFalafel! 🥙\2\3"
#  define SANDWICH	"\1\2\33[38;5;76ma sandwich! 🥪\2\3"
#  define FRIES		"\1\2\33[38;5;220mFrench fries! 🍟\2\3"
#  define HAMBURG	"\1\2\33[38;5;171ma Hamburger! 🍔\2\3"
#  define LUFFY		"\1\2\33[38;5;195mLike Luffy 🍖🍗🥓\2\3"
#  define FRENCH	"\1\2\33[38;5;130mBaguette 🥖 hon hon hon\2\3"
#  define CURRY		"\1\2\33[38;5;99mCurry! 🍛\2\3"
#  define SALAD		"\1\2\33[38;5;118mSalad! 🥗\2\3"
#  define SUSHI		"\1\2\33[38;5;198mSushi! 🍣\2\3"
#  define AVOCA		"\1\2\33[38;5;34m Avocado Toast! 🥑🍞\2\3"
#  define MANGO		"\1\2\33[38;5;119mMango! 🥭\2\3"
#  define CHERRY	"\1\2\33[38;5;196mCherries! 🍒\2\3"
#  define DONUT		"\1\2\33[38;5;93mDoughnuts! 🍩\2\3"
#  define PANCAKE	"\1\2\33[38;5;27mPancakes! 🥞\2\3"
#  define APPLE2	"\1\2\33[38;5;76man apple! 🍏\2\3"
#  define KIWI		"\1\2\33[38;5;71mKiwis! 🥝\2\3"
#  define CHEESE	"\1\2\33[38;5;226mCheese! 🧀\2\3"
#  define SHEPPIE	"\1\2\33[38;5;178mShepard's pie! 🥧\2\3"
#  define PEACHES	"\1\2\33[38;5;204mPeaches! 🍑!\2\3"
#  define WATERM	"\1\2\33[38;5;28mWatermelon! 🍉\2\3"
#  define EGG		"\1\2\33[38;5;231mEgg. 🥚! 🌭\2\3"
#  define COCONUT	"\1\2\33[38;5;252mCoconut! 🥥\2\3"
#  define CARROT	"\1\2\33[38;5;202mCarrots! 🥕\2\3"
#  define SHRIMP	"\1\2\33[38;5;206mShrimp! 🍤\2\3"
#  define CAKE		"\1\2\33[38;5;214mCake! 🍰\2\3"
#  define HOTDOGS	"\1\2\33[38;5;88mHotdogs! 🌭\2\3"
# endif

#endif