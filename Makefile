NAME = get_line.a

NUM = 5

SRC = get_next_line.c get_next_line_utils.c main.c
		
OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror # -D BUFFER_SIZE=$(NUM)

$(NAME): $(OBJS)
	@ar r $(NAME) $(OBJS)
	@echo "\033[1;105mWork compile\033[0m"

%.o : %.c ./get_next_line.h
	@gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

run: all
	@tput setaf 214; echo "MAKEFLE DE GET_NEXT_LINE"
	@gcc $(CFLAGS) $(NAME) -g3 -o gnl.out  
	./gnl.out |cat -e

debug: all
	@gcc $(CFLAGS) $(SRC) -g3 -o gnl.out
	@tput setaf 214; echo "DEBUG"
normi:
	norminette $(SRC) ./get_next_line.h
	@tput setaf 153; echo "Norminette"

clean:
	@rm -f gnl.out $(OBJS)

fclean: clean
	@rm -f $(NAME)
	
re:	fclean run

PHONY.: clean all
