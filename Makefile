# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/25 19:44:15 by agaladi           #+#    #+#              #
#    Updated: 2024/08/26 23:18:40 by agaladi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
SRCS = philo.c utils.c custom_functions.c parsing.c init.c philo_utils.c print.c dinner.c monitor.c 
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread
ORANGE = \033[38;5;214m
COLOR = \033[38;5;51m
RED	= \033[38;5;196m
GREEN = \033[32m
RESET = \033[0m
DEPS = philo.h
OBJS = $(SRCS:.c=.o)
OUT = philo

define PRINT_LOADING
	@printf "$(COLOR)Compiling src/$*.c... ["
	@for i in $(shell seq 0 20); do \
		printf "\r$(COLOR)Compiling src/$*.c... ["; \
		for j in $$(seq 1 $$i); do printf "▓"; done; \
		printf "]$(RESET)"; \
	done; \
	printf "$(GREEN)Done\n$(RESET)"
endef

all: $(OUT)

$(OUT): $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(OUT)

%.o: %.c $(DEPS)
	$(PRINT_LOADING)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(OUT)

re: fclean all

rec: re
	@make clean
