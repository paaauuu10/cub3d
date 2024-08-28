# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pborrull <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 14:17:08 by pborrull          #+#    #+#              #
#    Updated: 2024/08/28 09:23:16 by pborrull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED = \033[1;31m
MAGENTA = \033[1;35m
BLUE = \033[38;5;75m
ORIGINAL = \033[0m

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

INCS = -I./include/ -I./include/Libft
LIBFTA = -L./include/libft -lft
LIBFT = include/libft
SRCDIR = src/
MLX = include/libx/
OBJDIR = obj/
MINI = -L$(MLX) -lmlx -lXext -lX11 -lm  
SRC_L = main.c map.c movs.c exit.c
SRC = $(addprefix $(SRCDIR), $(SRC_L))
OBJECTS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all:
	@make -C $(LIBFT) > /dev/null
	@make -C $(MLX) > /dev/null
	@make $(NAME)

$(OBJDIR)%.o: %.c  
	@mkdir -p $(@D)
	@clang $(CFLAGS) $(INCS) -c $< -o $@
	@echo "$(GREEN)[OK]       $(CYAN)Compiled$(ORIGINAL)"

$(NAME): $(OBJECTS) Makefile
	@mkdir -p $(@D)
	@cc $(CFLAGS) -o $@ $(OBJECTS) $(LIBFTA) $(MINI)
	@echo  "$(GREEN)[OK]       $(YELLOW)All Compiled$(ORIGINAL)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT) > /dev/null
	@echo  "$(RED)[OK]       $(MAGENTA)All Very Clean$(ORIGINAL)"

clean:
	@rm -rf $(OBJDIR)
	@rm -f .temp
	@make clean -C $(LIBFT) > /dev/null
	@echo "$(RED)[OK]       $(BLUE)All Clean$(ORIGINAL)"

re: fclean all

.PHONY: all clean fclean re
