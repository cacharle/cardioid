RM = rm -f
MKDIR = mkdir -p

NAME = cardioid

SRCDIR = src
INCDIR = inc
OBJDIR = obj

CC = gcc
CCFLAGS = -Wall -Wextra -I$(INCDIR) $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lm

SRC = $(shell find $(SRCDIR) -type f -name "*.c")
INC = $(shell find $(INCDIR) -type f -name "*.h")
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: prebuild $(NAME)

prebuild:
	$(MKDIR) $(OBJDIR)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
