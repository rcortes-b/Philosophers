NAME = philo

CC = gcc
FLAGS = -Wall -Wextra -Werror -O3 -pthread -fsanitize=thread
RM = rm -rf

SRCS = srcs/philo.c srcs/parse.c srcs/utils.c srcs/routine.c \
		srcs/routine_utils.c srcs/print.c

OBJS = $(SRCS:.c=.o)

HEAD = includes/philo.h

all : $(NAME)

%.o : %.c Makefile $(HEAD)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
