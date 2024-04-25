CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER_CFILES := server.c
CLIENT_CFILES := client.c

OBJDIR := obj
SERVER_OFILES := $(addprefix $(OBJDIR)/, $(SERVER_CFILES:.c=.o))
CLIENT_OFILES := $(addprefix $(OBJDIR)/, $(CLIENT_CFILES:.c=.o))

NAME := minitalk
NAME_SERVER := server
NAME_CLIENT := client

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -L$(LIBFT_DIR) -lft

INC_DIR := .
HEADER := minitalk.h
HEADER := $(addprefix $(INC_DIR)/, $(HEADER))

all: $(NAME)

$(NAME): $(NAME_SERVER) $(NAME_CLIENT)

bonus: all

$(NAME_SERVER): $(LIBFT) $(SERVER_OFILES)
	@echo "$(YELLOW)Compiling server...$(NC)"
	$(CC) $(CFLAGS) -o $@ $(SERVER_OFILES) $(LIBFT_FLAGS)

$(NAME_CLIENT): $(LIBFT) $(CLIENT_OFILES)
	@echo "$(YELLOW)Compiling client...$(NC)"
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OFILES) $(LIBFT_FLAGS)

$(OBJDIR)/%.o: %.c $(HEADER) | $(OBJDIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I. -I$(INC_DIR) -c $< -o $@

$(OBJDIR):
	@echo "$(YELLOW)Creating obj directory...$(NC)"
	@mkdir -p $(OBJDIR)

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(NC)"
	if [ ! -d $(LIBFT_DIR) ]; then mkdir -p $(LIBFT_DIR); fi
	@git submodule update --init --recursive
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "$(RED)Removing object files...$(NC)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Removing binary files...$(NC)"
	@rm -f $(NAME_SERVER)
	@rm -f $(NAME_CLIENT)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re $(NAME)

# colors:
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m
