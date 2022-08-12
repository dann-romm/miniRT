CC					= gcc
RM					= rm -rf
CFLAGS				= -O2 -MMD

# program's name
NAME				= librender.a

# directories
SRCDIR				= ./src
OBJDIR				= ./build
INCDIR				= ./includes

CAMERA_SRCDIR		= $(SRCDIR)/camera
CANVAS_SRCDIR		= $(SRCDIR)/canvas
COLOR_SRCDIR		= $(SRCDIR)/color
KDTREE_SRCDIR		= $(SRCDIR)/kdtree
POINT_SRCDIR		= $(SRCDIR)/point
RENDER_SRCDIR		= $(SRCDIR)/render
SCENE_SRCDIR		= $(SRCDIR)/scene
UTILS_FT_SRCDIR		= $(SRCDIR)/utils_ft
UTILS_MATH_SRCDIR	= $(SRCDIR)/utils_math
VECTOR_SRCDIR		= $(SRCDIR)/vector

# source files
CAMERA_SRC			=	$(CAMERA_SRCDIR)/camera.c

CANVAS_SRC			=	$(CANVAS_SRCDIR)/canvas.c

COLOR_SRC			=	$(COLOR_SRCDIR)/color.c

KDTREE_SRC			=	$(KDTREE_SRCDIR)/kdtree.c \
						$(KDTREE_SRCDIR)/voxel.c

POINT_SRC			=	$(POINT_SRCDIR)/point.c \
						$(POINT_SRCDIR)/rotate_point.c

RENDER_SRC			=	$(RENDER_SRCDIR)/reflect_ray.c \
						$(RENDER_SRCDIR)/render.c \
						$(RENDER_SRCDIR)/tracer.c

SCENE_SRC			=	$(SCENE_SRCDIR)/scene.c \
						$(SCENE_SRCDIR)/fog.c

UTILS_FT_SRC		=	$(UTILS_FT_SRCDIR)/ft_bzero.c \
						$(UTILS_FT_SRCDIR)/ft_calloc.c \
						$(UTILS_FT_SRCDIR)/ft_memset.c \
						$(UTILS_FT_SRCDIR)/ft_memcpy.c

UTILS_MATH_SRC		=	$(UTILS_MATH_SRCDIR)/utils_double.c

VECTOR_SRC			=	$(VECTOR_SRCDIR)/vector.c \
						$(VECTOR_SRCDIR)/vector_product.c \
						$(VECTOR_SRCDIR)/vector_utils.c \
						$(VECTOR_SRCDIR)/rotate_vector.c \
						$(VECTOR_SRCDIR)/matrix.c

SRC					=	$(CAMERA_SRC) \
						$(CANVAS_SRC) \
						$(COLOR_SRC) \
						$(KDTREE_SRC) \
						$(POINT_SRC) \
						$(RENDER_SRC) \
						$(SCENE_SRC) \
						$(UTILS_FT_SRC) \
						$(UTILS_MATH_SRC) \
						$(VECTOR_SRC)

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
