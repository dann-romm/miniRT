CC				= gcc
RM				= rm -rf
# CFLAGS			= -Wall -Wextra -Werror -Ofast -MMD
CFLAGS			= -Ofast -MMD

# program's name
NAME			= miniRT

# directories
SRCDIR			= ./src
UTILS_SRCDIR	= $(SRCDIR)/utils

OBJDIR			= ./build
INCDIR			= ./includes

# source files
UTILS_SRC		=	$(UTILS_SRCDIR)/ft_bzero.c \
					$(UTILS_SRCDIR)/ft_calloc.c

SRC				=	$(SRCDIR)/main.c \
					$(SRCDIR)/color.c \
					$(UTILS_SRC)

# object files and dependency files
OBJ				= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP				= $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
