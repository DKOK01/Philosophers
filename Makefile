CC		= cc
CFLAGS	= -Wall -Wextra -Werror

GREEN = \033[1;32m
BLUE = \033[1;34m
PURPLE = \033[1;35m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED = \033[1;31m
RESET = \033[0m

SRC		= 

OBJ		= $(SRC:.c=.o)

NAME	= philo

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Philo compiled successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(YELLOW)Cleaning object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Philo cleaned successfully!$(RESET)"

re: fclean all
	@echo "$(BLUE)Philo rebuilt successfully!$(RESET)"