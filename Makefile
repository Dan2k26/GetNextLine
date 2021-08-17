NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c\
		ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c\
		ft_memset.c ft_strchr.c ft_strdup.c ft_strjoin.c\
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c\
		ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c\
		ft_toupper.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_strmapi.c \
		ft_striteri.c
		

OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pedantic -O3 #optimizacion de codigo = O3, informacion de todo lo fallido con premeditacion alevosia y blabla -pedantic

$(NAME): $(OBJS)
	@ar r $(NAME) $(OBJS)
	@echo "\033[1;105mLibft hecho\033[0m"

%.o : %.c libft.h
	@gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

run: all
	@tput setaf 153; echo "MAKEFLE DE LIBFT"
	@gcc libft.a -g3 -o a.out  
#g flag para el debugging
	./a.out

normi:
	norminette $(SRC) ./libft.h
	@tput setaf 153; echo "Norminette"

clean:
	@rm -f *.o $(NAME)

fclean:
	@rm -f $(NAME)
	
re:	clean run

PHONY.: clean all
