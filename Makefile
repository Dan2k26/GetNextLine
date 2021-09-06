NAME = get_line.a

NUM = 5

SRC = get_next_line.c get_next_line_utils.c main.c

SRCDEBUG = get_next_line.c get_next_line_utils.c main_debug.c
		
OBJS = $(SRC:.c=.o)

OBJSDEBUG = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror # -D BUFFER_SIZE=$(NUM)

all: $(NAME)

#gcc get_next_line.c get_next_line_utils.c main_debug.c -fsanitize=address -o gnl.out

$(NAME): $(OBJSDEBUG)
	ar r $(NAME) $(OBJS) $(OBJSDEBUG)
	@echo "\033[1;105mWork compile\033[0m"

run: all
	@tput setaf 214; echo "MAKEFLE DE GET_NEXT_LINE"
	@gcc $(CFLAGS) $(NAME) -g3 -o gnl.out  
	./gnl.out ficheros/$(filter-out $@,$(MAKECMDGOALS)) |cat -e

debug: 
	gcc $(SRCDEBUG) -g3  -o gnl.out 
	@tput setaf 214; echo "DEBUG"

normi:
	norminette $(SRC) ./get_next_line.h

clean:
	@rm -f gnl.out $(OBJS)

fclean: clean
	@rm -f $(NAME)
	
re:	fclean run

PHONY.: clean all
