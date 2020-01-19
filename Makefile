CC=clang
CFLAGS=-Wextra -Wall -g 
CFLAGS+=-Iinc -Ilibft
LFLAGS=-L libft -lft -Wl,-export_dynamic
DLFLAGS=-shared -fPIC
SRC=$(wildcard src/*)
OBJ=$(SRC:src/%.c=%.o)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)-$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so

.PHONY: clean fclean all re norm norme debug test norman

VPATH = src obj

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(LFLAGS) $(DLFLAGS) -o $(NAME) obj/*
	@echo "build complete!"

all: $(NAME)

%.o: %.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -o obj/$@ -c $<

clean:
	@rm -rf obj/

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: $(NAME)
	$(CC) -o test main.c $(NAME) -g -Wl,-export_dynamic
