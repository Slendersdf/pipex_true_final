NAME = libft.a

COMP = gcc -Wall -Wextra -Werror -I ./

MANDATORY =	ft_putstr_fd.c ft_split.c ft_strlcpy.c \
				ft_strchr.c ft_strdup.c ft_strjoin.c \
					ft_strlen.c ft_strncmp.c ft_strnstr.c \
						ft_strtrim.c ft_substr.c ft_calloc.c \
							ft_putchar_fd.c ft_strcmp.c \

OBJ_MANDATORY = ${MANDATORY:.c=.o}

%.o: %.c
	${COMP} -c $< -o ${<:.c=.o}

all: ${NAME}

$(NAME): ${OBJ_MANDATORY}
	ar rcs ${NAME} ${OBJ_MANDATORY}

clean:
	rm -f ${OBJ_MANDATORY}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
