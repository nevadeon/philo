NAME := philo

# Compiler, flags and args
CC := cc
CFLAGS = -Wall -Wextra -Werror -pthread -o3 -I$(INC_DIR)
LDFLAGS =
VALGRIND_FLAGS := --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes
GDB_FLAGS := --quiet --args
GDB_VALGRIND_ARGS = 1 410 200 200

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

valgrind: CFLAGS += -g -fsanitize=thread
valgrind: re
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(GDB_VALGRIND_ARGS)

gdb: CFLAGS += -g -fsanitize=thread
gdb: re
	gdb $(GDB_FLAGS) ./$(NAME) $(GDB_VALGRIND_ARGS)

.PHONY: all re clean fclean valgrind gdb
