NAME = pipex

LIBFT_DIRECTORY = libft

LIBFT = $(LIBFT_DIRECTORY)/libft.a

COMP = cc -Wall -Wextra -Werror -I ./

MANDATORY = src/pipex.c src/pipex_utils.c src/pipex_proc.c \

OBJS = $(MANDATORY:.c=.o)

%.o: %.c
	${COMP} -c $< -o ${<:.c=.o}

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIRECTORY) all

$(NAME): $(OBJS) $(LIBFT)
	$(COMP) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIRECTORY)
	rm -f $(OBJS)
	rm -f $(LIBFT_DIRECTORY)/*.o

fclean: clean
	make fclean -C $(LIBFT_DIRECTORY)
	rm -f $(NAME)
	rm -f $(LIBFT_DIRECTORY)/*.o

re: fclean all

.PHONY: all clean fclean re
