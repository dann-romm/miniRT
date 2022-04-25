CC			= gcc
RM			= rm -rf
# CFLAGS		= -Wall -Wextra -Werror -Ofast -MMD
CFLAGS		= -Ofast -MMD

NAME		= miniRT

SRCDIR		= ./src
OBJDIR		= ./build
INCDIR		= ./includes

SRC			=	$(SRCDIR)/main.c \
				$(SRCDIR)/color.c

OBJ			= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP			= $(OBJ:.o=.d)

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
