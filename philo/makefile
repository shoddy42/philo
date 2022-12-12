# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: wkonings <wkonings@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 16:21:56 by wkonings      #+#    #+#                  #
#    Updated: 2022/12/08 18:16:27 by wkonings      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#todo: make Makefile always call make on library makefile to make sure ITS make is upto date.
#todo: also make sure the header is up to date when constructing .o files i think
# --------------- VARIABLES ---------------#


#todo: FLAGS
NAME = philo
FLAGS = -Wall -Wextra -Werror -pthread
DEBUG = -g -fsanitize=thread
CC = gcc

# --------------- DIRECTORIES ------------ #

SRC_DIR		:= src
OBJ_DIR		:= obj
BIN_DIR		:= bin
INCLUDE_DIR	:= include

HEADERS_DIR	:= include
INC			:= -I include

# --------------- FILES -------------------#

HEADER_FILES:=  philosophers.h print.h
HEADERS		:=	$(addprefix $(INCLUDE_DIR)/, $(HEADER_FILES))

FILES		:=	philosophers gods poet utils init init_utils fancy

SRCS		:=	$(addprefix $(SRC_DIR)/,$(FILES:%=%.c))
OBJS		:=	$(addprefix $(OBJ_DIR)/,$(notdir $(SRCS:%.c=%.o)))

MAKEFILE	:= makefile

# -----------------------------------------#
# --------------- RECIPES -----------------#
# -----------------------------------------#

$(NAME): $(OBJS) $(HEADERS) $(MAKEFILE)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(INCLUDES)

debug: $(OBJS) $(HEADERS) $(MAKEFILE)
	$(CC) $(DEBUG) $(SRCS) -o $(NAME) $(INC) $(INCLUDES)

fancy: $(OBJS) $(HEADERS) $(MAKEFILE)
	$(CC) $(FLAGS) -D FANCY=1 $(SRCS) -o $(NAME) $(INC) $(INCLUDES)

normal: $(OBJS) $(HEADERS) $(MAKEFILE)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(INCLUDES)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo Creating file.
	$(CC) $(FLAGS) $(INC) $(INCLUDE_READLINE) -c $< -o $@

flags:
	gcc $(FLAGS) $(SOURCES) -lft $(INCLUDES)
	./$(NAME)

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean:	clean
	/bin/rm -f $(NAME)

re: fclean all

test: $(NAME)
	./$(NAME)

pog:
	@echo ⣿⣿⣿⣿⡿⠟⠛⠛⠛⠛⠉⠉⠙⠛⠛⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠟
	@echo ⣿⣿⣯⣥⣤⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⣏⣀⣀⣀⡀
	@echo ⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠻⠿⠟⠉⠉⠉⢻⣿⣿⣿⡿⠟⠋⣡⣼⣿⣿⣿⡄
	@echo ⣿⣿⣿⣟⣭⣤⣶⣶⣿⣿⠃⠀⠀⢀⣀⣤⣶⣿⣿⣿⣿⡅⡀⢀⣩⣤⣤
	@echo ⣿⣿⣿⣿⣿⣿⣛⡛⠛⠛⠛⢋⣩⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣛⠛⠛⠓⠠
	@echo ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣤⣤⣤⣦
	@echo ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇
	@echo ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠿⢿⡿⢿⣿⣿⣿⠃
	@echo ⠿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣥⣄⣀⣀⠀⠀⠀⠀⠀⢰⣾⣿⣿⠏
	@echo ⠀⠀⠀⠀⠀⠀⠉⣩⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣜⡻⠋
	@echo ⣰⣾⣷⣶⣿⣾⣖⣻⣿⣿⡿⣿⣿⣿⣿⠿⠿⠟⠛⠛⠛⠋⠉⠉⢉⡽⠃
	@echo ⣿⣿⣿⣿⣿⣿⡉⠉⠉⠛⠛⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⡤⠚⠉
	@echo ⠛⠛⣿⣿⣿⣿⣿⣿⣿⠉⠛⢶⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⡇
	@echo ⠠⣾⣿⣿⣿⣿⣿⠿⠟⠃⠀⠀⠀⠈⠲⣴⣦⣤⣤⣤⣶⡾⠁
	@echo ⠄⠈⠉⠻⢿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠛⠛⠉

.PHONY: all clean fclean re test fancy debug pog flags
