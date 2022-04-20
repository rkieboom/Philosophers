# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rkieboom <rkieboom@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/03 16:05:06 by rkieboom      #+#    #+#                  #
#    Updated: 2022/04/20 23:22:25 by rkieboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ================================ VARIABLES ================================= #

# The name of your executable
NAME		= philo

# Compiler and compiling flags
CC	= gcc
CFLAGS	= -pthread

# Debug, use with`make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS	+= -g3
endif
ifeq ($(DEBUG),2)
CFLAGS	+= -g3 -fsanitize=address
endif
ifeq ($(DEBUG),3)
CFLAGS	+= -g3 -fsanitize=thread
endif

# Folder name
SRCDIR	= ./
OBJDIR	= bin/

SRCS =	main.c $(SRCS_FUNCTIONS) $(SRCS_FORKS) $(SRCS_PHILO) $(SRCS_THREADS) $(SRCS_MONITORING_THREAD)

SRCS_FUNCTIONS =	functions/ft_calloc.c functions/get_time.c functions/ft_strlen.c \
					functions/ft_atoi.c functions/ft_atoi_l.c functions/ft_isdigit.c \
					functions/ft_write_error.c functions/lexer.c functions/parse.c \
					functions/ft_bzero.c

SRCS_FORKS = 		forks/init_forks.c

SRCS_PHILO = 		philos/philo.c philos/setup_philos.c $(SRCS_PHILO_FUNC)

SRCS_PHILO_FUNC = 	philos/functions/eat.c philos/functions/ft_eaten_enough.c \
					philos/functions/sleep.c philos/functions/stop.c \
					philos/functions/take_forks.c philos/functions/think.c

SRCS_THREADS = 		threads/create_and_start_threads.c

SRCS_MONITORING_THREAD =	monitoring_thread/monitoring_thread.c

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
	./$(NAME) 8 800 200 200

# This specifies the rules that does not correspond to any filename
.PHONY	= all run clean fclean re