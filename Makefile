CC					= gcc
RM					= rm -rf
CFLAGS				= -Ofast -MMD

# program's name
NAME				= miniRT
LIBRENDERNAME		= librender.a

# directories
SRCDIR				= ./src
OBJDIR				= ./build
INCDIR				= ./includes
LIBRENDERDIR		= ./librender

PLANE_SRCDIR		= $(SRCDIR)/plane

SPHERE_SRCDIR		= $(SRCDIR)/sphere

UTILS_MATH_SRCDIR	= $(SRCDIR)/utils_math

# source files
PLANE_SRC			=	$(PLANE_SRCDIR)/plane.c \
						$(PLANE_SRCDIR)/plane_get_funcs.c \
						$(PLANE_SRCDIR)/plane_intersect.c

SPHERE_SRC			=	$(SPHERE_SRCDIR)/sphere.c \
						$(SPHERE_SRCDIR)/sphere_get_funcs.c \
						$(SPHERE_SRCDIR)/sphere_intersect.c

UTILS_MATH_SRC		=	$(UTILS_MATH_SRCDIR)/utils_math.c

SRC					=	$(SRCDIR)/main.c \
						$(SPHERE_SRC) \
						$(UTILS_MATH_SRC)

# object files and dependency files
OBJ					= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP					= $(OBJ:.o=.d)

# build rules
all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBRENDERDIR)
	cp $(LIBRENDERDIR)/$(LIBRENDERNAME) ./$(LIBRENDERNAME)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./ -lrender

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -I$(LIBRENDERDIR)/includes

clean:
	make clean -C $(LIBRENDERDIR)
	$(RM) $(OBJDIR)

fclean: clean
	make fclean -C $(LIBRENDERDIR)
	$(RM) $(NAME)
	$(RM) $(LIBRENDERNAME)

re: fclean all

# include dependencies
-include $(DEP)

# these are not filenames
.PHONY: all clean fclean re
