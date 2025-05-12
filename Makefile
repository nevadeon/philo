NAME := philo

# Compiler, flags and args
CC := cc
CFLAGS = -Wall -Wextra -Werror -pthread -o3 -I$(INC_DIR)
LDFLAGS =
VALGRIND_FLAGS := --quiet --leak-check=full --show-leak-kinds=all
GDB_FLAGS := --quiet --args
ARGS = 5 2000 200 200 10

# Directories
INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj

# Sources and objects
SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# ============================================================================ #
#        Main rules                                                            #
# ============================================================================ #
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@./update_progress_bar.sh "Compiling $(NAME):"

re: fclean all

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

# ============================================================================ #
#        Test rules                                                            #
# ============================================================================ #

valgrind: CFLAGS += -g
valgrind: re
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)

gdb: CFLAGS += -g
gdb: re
	gdb $(GDB_FLAGS) ./$(NAME) $(ARGS)

.PHONY: all re clean fclean valgrind gdb
