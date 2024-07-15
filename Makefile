.PHONY : all clean fclean re debug

# Compiler
TARGET			= minishell
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
CFLAGS_DEBUG    = $(CFLAGS) -g

RM				= rm -rf
MKDIR			= mkdir -p
MAKE			= make -sC

# Libft
LIBFT_DIR		= libft/
LIBFT_A			= libft.a
LIBFT			= $(addprefix $(LIBFT_DIR), $(LIBFT_A))

# Includes
INCLUDES_DIR	= include
INCLUDES_FLAG	= -I$(INCLUDES_DIR) -I$(LIBFT_DIR)
INCLUDES		= $(wildcard $(INCLUDES_DIR)/*.h) $(LIBFT_DIR)/libft.h

# Sources
SOURCES_DIR		= src/
SOURCE_FILES	= $(wildcard $(SOURCES_DIR)/*.c)

# Object files
OBJS_DIR		= objs/
OBJS			= $(SOURCE_FILES:$(SOURCES_DIR)%.c=$(OBJS_DIR)%.o)

LINKER			= -lft -L $(LIBFT_DIR) -lreadline

# Colors
RESET			= "\033[0m"
BLACK    		= "\033[30m"    # Black
RED      		= "\033[31m"    # Red
GREEN    		= "\033[32m"    # Green
YELLOW   		= "\033[33m"    # Yellow
BLUE     		= "\033[34m"    # Blue
MAGENTA  		= "\033[35m"    # Magenta
CYAN     		= "\033[36m"    # Cyan
WHITE    		= "\033[37m"    # White


all : $(LIBFT) $(OBJS_DIR) $(TARGET)

$(LIBFT) :
	@echo $(BLUE) "-- Creating Libft" $(RESET)
	@$(MAKE) $(LIBFT_DIR)

$(OBJS_DIR) :
	@$(MKDIR) $(OBJS_DIR)

$(TARGET) : $(OBJS) Makefile
	@echo $(GREEN) "-- Creating $(TARGET)" $(RESET)
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) -o $(TARGET)

$(OBJS_DIR)%.o : $(SOURCES_DIR)%.c $(INCLUDES)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAG) -c $< -o $@

clean :
	@$(RM) $(OBJS_DIR)
	@echo $(MAGENTA) "-- Removing Object Files" $(RESET)

fclean : clean
	@$(RM) $(TARGET)
	@$(MAKE) $(LIBFT_DIR) fclean
	@echo $(RED) "-- Removing Libft and $(TARGET)" $(RESET)

re : fclean all

debug : $(CFLAGS) = $(CFLAGS_DEBUG)
debug : re