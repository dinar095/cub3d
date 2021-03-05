NAME		= cub3D

SRCS	= parser/check_map/check_valid.c \
			parser/gnl/get_next_line.c \
			parser/gnl/get_next_line_utils.c \
			parser/srcs/ft_header.c \
			parser/parser.c \
			main.c \
			game/srcs.c \

OBJS		= $(patsubst %.c, %.o, $(SRCS))



CC			= gcc
FLAGS		= #-Wall -Wextra -Werror
HEADER		= game/ft_game.h

RM			= rm -f

all:		init ${NAME}

init:
			@ echo "......init...LINUX..."
			make -C libft
			make -C linminilibx
$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(FLAGS) ${OBJS} $(HEADER) -Llibft -lft -Llinminilibx -lmlx -lX11 -lm -lXext -lbsd -o $(NAME)


%.o : %.c
			${CC} $(FLAGS) -c $< -o $@

clean:
			${RM} ${OBJS} ${BOBJS} *.out
			make -C libft clean

fclean:		clean
			$(RM) -rf $(NAME)
			make -C libft fclean


# 		!!!!!!!!	ADD FCLEAN FOR MLX          !!!!!!!!


re:			fclean all

.PHONY:		all clean fclean re

# commands
# http://rus-linux.net/nlib.php?name=/MyLDP/algol/gnu_make/gnu_make_3-79_russian_manual.html#SEC77