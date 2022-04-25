CC					= gcc
RM					= rm -rf
# CFLAGS				= -Wall -Wextra -Werror -Ofast -MMD
CFLAGS				= -Ofast -MMD

# program's name	
NAME				= miniRT

# directories	
SRCDIR				= ./src
OBJDIR				= ./build
INCDIR				= ./includes

CANVAS_SRCDIR		= $(SRCDIR)/canvas
COLOR_SRCDIR		= $(SRCDIR)/color
UTILS_FT_SRCDIR		= $(SRCDIR)/utils_ft
UTILS_SRCDIR		= $(SRCDIR)/utils

# source files
CANVAS_SRC			=	$(CANVAS_SRCDIR)/canvas.c

COLOR_SRC			=	$(COLOR_SRCDIR)/color.c

UTILS_SRC			=	$(UTILS_SRCDIR)/reflect_ray.c \
						$(UTILS_SRCDIR)/rotate_point.c \
						$(UTILS_SRCDIR)/rotate_vector.c \
						$(UTILS_SRCDIR)/vector_product.c \
						$(UTILS_SRCDIR)/vector_utils.c

UTILS_FT_SRC		=	$(UTILS_FT_SRCDIR)/ft_bzero.c \
						$(UTILS_FT_SRCDIR)/ft_calloc.c \
						$(UTILS_FT_SRCDIR)/ft_memset.c

SRC					=	$(SRCDIR)/main.c \
						$(SRCDIR)/point.c \
						$(SRCDIR)/vector.c \
						$(CANVAS_SRC) \
						$(COLOR_SRC) \
						$(UTILS_SRC) \
						$(UTILS_FT_SRC)

# object files and dependency files
OBJ					= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP					= $(OBJ:.o=.d)

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
