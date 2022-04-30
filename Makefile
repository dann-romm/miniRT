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

# source files
SRC					=	$(SRCDIR)/main.c

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
