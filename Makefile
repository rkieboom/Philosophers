# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rkieboom <rkieboom@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/03 16:05:06 by rkieboom      #+#    #+#                  #
#    Updated: 2022/04/02 19:42:32 by rkieboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ================================ VARIABLES ================================= #

# The name of your executable
NAME		= philo

# Compiler and compiling flags
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -pthread

# Debug, use with`make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS	+= -g3
endif

# Folder name
SRCDIR	= ./
OBJDIR	= bin/

SRCS =	main.c $(SRCS_FORKS) $(SRCS_FUNC) $(SRCS_PHILO) $(SRCS_MONITORING) $(SRCS_THREADS)

SRCS_FORKS =	forks/create_fork.c forks/fork_add_back_last.c forks/fork_add_back.c \
				forks/fork_add_front.c forks/fork_last.c forks/ft_free_forks.c \
				forks/init_forks.c

SRCS_FUNC =		functions/ft_calloc.c functions/get_time.c functions/ft_strlen.c \
				functions/ft_atoi.c functions/ft_atoi_l.c functions/ft_isdigit.c \
				functions/ft_write_error.c functions/read_and_lexer.c \
				functions/ft_free_all.c

SRCS_PHILO =	philosopher/philo.c philosopher/ft_think.c philosopher/ft_take_forks.c \
				philosopher/ft_sleep.c philosopher/ft_eat.c philosopher/philo_died.c

SRCS_MONITORING =	monitoring_thread.c

SRCS_THREADS =	threads/create_threads.c threads/join_threads.c

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.c=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

SRC_B		:= $(notdir $(SRCS.BONUS))
OBJ_B		:= $(SRC_B:.c=.o)
OBJS_B	:= $(addprefix $(OBJDIR), $(OBJ_B))

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# Implicit rules
VPATH := $(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)

# ================================== RULES =================================== #

all : $(NAME)

# Compiling
$(OBJDIR)%.o : %.c
	@mkdir -p $(OBJDIR)
	@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking
$(NAME)	: $(SRCS)  $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRC)$(RC)\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
# Cleaning
clean :
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@rm -rf $(OBJDIR)

fclean : clean
	@printf "$(RE)--- Removing $(NAME) & $(NAME_BONUS)$(RC)\n"
	@rm -f $(NAME)

# Special rule to force to remake everything
re : fclean all

# This runs the program
run : $(NAME)
	@printf "$(CY)>>> Running $(NAME)$(RC)\n"
	./$(NAME)

# This specifies the rules that does not correspond to any filename
.PHONY	= all run clean fclean re bonus