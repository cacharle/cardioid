RM = rm -f
MKDIR = mkdir -p

NAME = cardioid

CC = gcc
CCFLAGS = -Wall -Wextra -I$(INCDIR) $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lm

SRC = $(shell find . -type f -name "*.c")
INC = $(shell find . -type f -name "*.h")
OBJ = $(SRC:.c=.o)

all: $(NAME)

release: CCFLAGS += -D CARDIOID_RELEASE -Ofast
release: re

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c $(INC)
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
