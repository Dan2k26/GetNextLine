NAME = get_line.a

NUM = 42

SRC = prueba.c
		
OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=$(NUM)

$(NAME): $(OBJS)
	@ar r $(NAME) $(OBJS)
	@echo "\033[1;105mWork compile\033[0m"

%.o : %.c
	@gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

run: all
	@tput setaf 153; echo "MAKEFLE DE GET_LINE"
	@gcc get_line.a -g3 -o a.out  
	./a.out

normi:
	norminette $(SRC)
	@tput setaf 153; echo "Norminette"

clean:
	@rm -f a.out $(OBJS)

fclean: clean
	@rm -f $(NAME)
	
re:	fclean run

PHONY.: clean all
