NAME = pipex

NAME_BONUS = pipex_bonus

LIBFT_DIRECTORY = libft

LIBFT = $(LIBFT_DIRECTORY)/libft.a

COMP = cc -Wall -Wextra -Werror -I ./

MANDATORY = src/pipex.c src/pipex_utils.c src/pipex_proc.c \

BONUS = src_bonus/pipex_bonus.c src_bonus/pipex_proc_bonus.c src_bonus/pipex_utils_bonus.c \

OBJS = $(MANDATORY:.c=.o)

OBJS_BONUS = $(BONUS:.c=.o)

%.o: %.c
	${COMP} -c $< -o ${<:.c=.o}

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIRECTORY) all

$(NAME): $(OBJS) $(LIBFT)
	$(COMP) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(OBJS_BONUS) $(LIBFT)
	$(COMP) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

clean:
	make clean -C $(LIBFT_DIRECTORY)
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	rm -f $(LIBFT_DIRECTORY)/*.o

fclean: clean
	make fclean -C $(LIBFT_DIRECTORY)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	rm -f $(LIBFT_DIRECTORY)/*.o

re: fclean all

.PHONY: all clean fclean re
