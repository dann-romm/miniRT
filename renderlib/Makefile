CC					= gcc
RM					= rm -rf
CFLAGS				= -Ofast -MMD

# program's name
NAME				= renderlib.a

# directories
SRCDIR				= ./src
OBJDIR				= ./build
INCDIR				= ./includes

CANVAS_SRCDIR		= $(SRCDIR)/canvas
COLOR_SRCDIR		= $(SRCDIR)/color
KDTREE_SRCDIR		= $(SRCDIR)/kdtree
RENDER_SRCDIR		= $(SRCDIR)/render
SCENE_SRCDIR		= $(SRCDIR)/scene
UTILS_FT_SRCDIR		= $(SRCDIR)/utils_ft
UTILS_SRCDIR		= $(SRCDIR)/utils

# source files
CANVAS_SRC			=	$(CANVAS_SRCDIR)/canvas.c

COLOR_SRC			=	$(COLOR_SRCDIR)/color.c

KDTREE_SRC			=	$(KDTREE_SRCDIR)/kdtree.c

RENDER_SRC			=	$(RENDER_SRCDIR)/render.c \
						$(RENDER_SRCDIR)/tracer.c

SCENE_SRC			=	$(SCENE_SRCDIR)/scene.c \
						$(SCENE_SRCDIR)/fog.c

UTILS_SRC			=	$(UTILS_SRCDIR)/reflect_ray.c \
						$(UTILS_SRCDIR)/rotate_point.c \
						$(UTILS_SRCDIR)/rotate_vector.c \
						$(UTILS_SRCDIR)/vector_product.c \
						$(UTILS_SRCDIR)/vector_utils.c

UTILS_FT_SRC		=	$(UTILS_FT_SRCDIR)/ft_bzero.c \
						$(UTILS_FT_SRCDIR)/ft_calloc.c \
						$(UTILS_FT_SRCDIR)/ft_memset.c \
						$(UTILS_FT_SRCDIR)/ft_memcpy.c

SRC					=	$(SRCDIR)/camera.c \
						$(SRCDIR)/point.c \
						$(SRCDIR)/vector.c \
						$(CANVAS_SRC) \
						$(COLOR_SRC) \
						$(KDTREE_SRC) \
						$(RENDER_SRC) \
						$(SCENE_SRC) \
						$(UTILS_SRC) \
						$(UTILS_FT_SRC)

# object files and dependency files
OBJ					= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP					= $(OBJ:.o=.d)

# build rules
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# $(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# include dependencies
-include $(DEP)

# these are not filenames
.PHONY: all clean fclean re
