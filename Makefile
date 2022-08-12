CC					= gcc
RM					= rm -rf
CFLAGS				= -O2 -MMD

# program's name
NAME				= miniRT
RENDERNAME			= librender.a
MLXNAME				= libmlx.dylib
TESTNAME			= test

# directories
SRCDIR				= ./src
OBJDIR				= ./build
INCDIR				= ./includes
RENDERDIR			= ./librender
MLXDIR				= ./mlx

CYLINDER_SRCDIR		= $(SRCDIR)/cylinder
GNL_SRCDIR			= $(SRCDIR)/get_next_line
PARSER_SRCDIR		= $(SRCDIR)/parser
PLANE_SRCDIR		= $(SRCDIR)/plane
SPHERE_SRCDIR		= $(SRCDIR)/sphere
UTILS_FT_SRCDIR		= $(SRCDIR)/utils_ft
UTILS_MATH_SRCDIR	= $(SRCDIR)/utils_math

# source files
# CYLINDER_SRC		=	$(SRCDIR)/cylinder.c \

GNL_SRC				=	$(GNL_SRCDIR)/get_next_line.c \
						$(GNL_SRCDIR)/get_next_line_utils.c

PARSER_SRC			=	$(PARSER_SRCDIR)/parse_map.c \
						$(PARSER_SRCDIR)/parse_camera.c \
						$(PARSER_SRCDIR)/parse_utils.c

PLANE_SRC			=	$(PLANE_SRCDIR)/plane.c \
						$(PLANE_SRCDIR)/plane_get_funcs.c \
						$(PLANE_SRCDIR)/plane_intersect.c

SPHERE_SRC			=	$(SPHERE_SRCDIR)/sphere.c \
						$(SPHERE_SRCDIR)/sphere_get_funcs.c \
						$(SPHERE_SRCDIR)/sphere_intersect.c

UTILS_FT_SRC		=	$(UTILS_FT_SRCDIR)/ft_atof.c \
						$(UTILS_FT_SRCDIR)/ft_atoi.c \
						$(UTILS_FT_SRCDIR)/ft_strcmp.c \
						$(UTILS_FT_SRCDIR)/ft_strncmp.c

UTILS_MATH_SRC		=	$(UTILS_MATH_SRCDIR)/fov_to_proj_plane_dist.c \
						$(UTILS_MATH_SRCDIR)/solve_quadratic.c


SRC					=	$(GNL_SRC) \
						$(PARSER_SRC) \
						$(PLANE_SRC) \
						$(SPHERE_SRC) \
						$(UTILS_FT_SRC) \
						$(UTILS_MATH_SRC)

# object files and dependency files
OBJ					= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP					= $(OBJ:.o=.d)

# build rules
all: $(NAME)

$(NAME): $(OBJ) $(OBJDIR)/main.o $(RENDERNAME) $(MLXNAME)
	$(CC) $(CFLAGS) $(OBJ) $(OBJDIR)/main.o -o $(NAME) -L./ -lrender -lmlx

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -I$(RENDERDIR)/includes -I$(MLXDIR)

$(RENDERNAME):
	make -C $(RENDERDIR)
	cp $(RENDERDIR)/$(RENDERNAME) ./$(RENDERNAME)

$(MLXNAME):
	make -C $(MLXDIR)
	cp $(MLXDIR)/$(MLXNAME) ./$(MLXNAME)

clean:
	make clean -C $(RENDERDIR)
	make clean -C $(MLXDIR)
	$(RM) $(OBJDIR)

fclean: clean
	make fclean -C $(RENDERDIR)
	$(RM) $(NAME)
	$(RM) $(RENDERNAME)
	$(RM) $(TESTNAME)

re: fclean all

$(TESTNAME): $(OBJ) $(OBJDIR)/test.o
	make -C $(RENDERDIR)
	cp $(RENDERDIR)/$(RENDERNAME) ./$(RENDERNAME)
	$(CC) $(CFLAGS) $(OBJ) $(OBJDIR)/test.o -o $(TESTNAME) -L./ -lrender

# include dependencies
-include $(DEP)

# these are not filenames
.PHONY: all clean fclean re
