# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: florian <florian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 09:47:22 by fberthou          #+#    #+#              #
#    Updated: 2024/07/19 15:17:22 by florian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- SET COLORS --- #
RESET_COLOR	= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

# --- PROG NAME --- #
NAME		= philo

# --- SET PATHS --- #
#PROJECT#
HDR_PATH				= headers
SRC_PATH				= sources
MAIN_PATH				= $(SRC_PATH)/main
CHECK_ARGS_PATH			= $(SRC_PATH)/check_args
INIT_PATH				= $(SRC_PATH)/init
SIMULATION_PATH			= $(SRC_PATH)/simulation

#TEMPORARY FILES#
BUILD_PATH				= .build
BUILD_MAIN_PATH			= $(BUILD_PATH)/main
BUILD_CHECK_PATH		= $(BUILD_PATH)/check_args
BUILD_INIT_PATH			= $(BUILD_PATH)/init
BUILD_SIMULATION_PATH	= $(BUILD_PATH)/simulation

# --- COMPILATION FLAGS --- #
COMPFLAGS	=	-g #-fsanitize=thread #-Wall -Wextra -Werror

SRC		=	$(MAIN_PATH)/main.c $(MAIN_PATH)/utils.c $(MAIN_PATH)/init.c \
			\
			$(CHECK_ARGS_PATH)/check_args.c $(CHECK_ARGS_PATH)/check_utils.c \
			\
			$(SIMULATION_PATH)/philo.c $(SIMULATION_PATH)/simu_utils.c $(SIMULATION_PATH)/actions.c

### ---- TEMPORARY FILES ---- ###
OBJ	= $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

### --- CALL --- ###
default	: all
all		: $(NAME)

### --- PHILOSOPHERS --- ###
$(NAME)	: $(OBJ)
	$(CC) $(COMPFLAGS) -lpthread $^ -o $@
	@echo "$(GREEN)-- philo ready --$(RESET_COLOR)"

#######     OBJECTS    #######
$(BUILD_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(BUILD_PATH) $(BUILD_CHECK_PATH) $(BUILD_MAIN_PATH) $(BUILD_INIT_PATH) $(BUILD_SIMULATION_PATH)
	$(CC) $(COMPFLAGS) -I$(HDR_PATH) -c $< -o $@

### --- CLEAN MANAGEMENT --- ###
clean	:
	@rm -rf $(BUILD_PATH)
	@echo "$(YELLOW)-- removed temporary files --$(RESET_COLOR)"

fclean	:
	@rm -rf $(BUILD_PATH) $(NAME)
	@echo "$(YELLOW)-- removed philo --$(RESET_COLOR)"

re		: fclean all

.PHONY	: clean fclean re default all
