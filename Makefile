NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

RM = rm -f

SRCS = main.c utils.c philo.c monitor.c init.c eat.c utils_2.c time_function.c eat_3_philo.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
