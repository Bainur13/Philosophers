SRCS =			philosopher_main.c 	\
				initialize_philosopher.c	\
				philosopher_routine.c 	\
				start_threads.c			\
				arbitrator_routine.c		\
				utils.c

 CFLAGS =		-Wall -Werror -Wextra -g3  
#-pthread

# LDFLAGS = -L./libft -lft -pthread

NAME = philo

OBJS = $(SRCS:.c=.o)

# COLORS

GREEN = \033[0;32m
NC = \033[0m
YELLOW = \e[0;93m
RED = \033[0;31m

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo "	 			$(RED)+------------------------+\n \
					|  $(YELLOW)  PHILOSOPHER $(GREEN)[OK]$(RED)    |\n \
					+------------------------+$(NC)"

$(LIBFT):
	make -C ./libft

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

re: fclean
	make all

.PHONY: all clean fclean re