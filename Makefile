.PHONY : all clean fclean re

TARGET			= minishell
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g

RM				= rm -rf
MKDIR			= mkdir -p
MAKE			= make -sC


LIBFT_DIR		= libft/
LIBFT_A			= libft.a
LIBFT			= $(addprefix $(LIBFT_DIR), $(LIBFT_A))

HEADERS_DIR		= headers
HEADERS_FLAG	= -I$(HEADERS_DIR) -I$(LIBFT_DIR)
HEADERS			= $(wildcard $(HEADERS_DIR)/*.h) $(LIBFT_DIR)/libft.h

SOURCES_DIR		= sources/
SOURCE_FILES	= main.c \
				  tokenizer.c

SOURCES			= $(addprefix $(SOURCES_DIR), $(SOURCE_FILES))

OBJS_DIR		= objs/
OBJ_FILES		= $(SOURCE_FILES:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

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
	@echo $(BLUE) "  Creating Libft" $(RESET)
	@$(MAKE) $(LIBFT_DIR)

$(OBJS_DIR) :
	@$(MKDIR) $(OBJS_DIR)

$(TARGET) : $(OBJS) Makefile
	@echo $(GREEN) "  Creating $(TARGET)" $(RESET)
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) -o $(TARGET)

$(OBJS_DIR)%.o : $(SOURCES_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(HEADERS_FLAG) -c $< -o $@

clean :
	@$(RM) $(OBJS_DIR)
	@echo $(MAGENTA) "  Removing Object Files" $(RESET)

fclean : clean
	@$(RM) $(TARGET)
	@$(MAKE) $(LIBFT_DIR) fclean
	@echo $(RED) "  Removing Libft and $(TARGET)" $(RESET)

re : fclean all
