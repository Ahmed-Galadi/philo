CC = cc
SRCS = philo.c utils.c custom_functions.c parsing.c init.c philo_utils.c print.c dinner.c monitor.c 
CFLAGS = -Wall -Wextra -Werror -pthread
DEPS = philo.h
OBJS = $(SRCS:.c=.o)
OUT = philo

all: $(OUT)

$(OUT): $(OBJS) $(DEPS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(OUT)

re: fclean all