CC = cc
SRCS = philo.c utils.c costum_functions.c parsing.c init.c philo_utils.c print.c dinner.c monitor.c 
CFLAGS = -Wall -Wextra -Werror -pthread
DEPS = philo.h
LIB = philo.a
OUT = philo
OBJS = $(SRCS:.c=.o)

all: $(OUT)

$(OUT): $(LIB) $(DEPS)
	$(CC) $(CFLAGS) $(MLX) philo.c $(LIB) -o $(OUT)

$(LIB): $(OBJS)
	ar -rc $(LIB) $(OBJS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJS) $(LIB)

fclean: clean
	rm -rf $(LIB) $(OUT)

re: fclean all
