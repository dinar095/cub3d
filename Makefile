NAME		= cub3D

SRCS	= parser/check_map/check_valid.c \
			parser/gnl/get_next_line.c \
			parser/gnl/get_next_line_utils.c \
			parser/srcs/ft_header.c \
			parser/srcs/cheakers.c \
			parser/parser.c \
			main.c \
			game/srcs.c \

OBJS		= $(patsubst %.c, %.o, $(SRCS))



CC			= gcc
FLAGS		= -Wall -Wextra -Werror
HEADER		= game/ft_game.h

RM			= rm -f

all:		init ${NAME}

init:
			make -C libft
			make -C libmlx_mac
$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(FLAGS) ${OBJS} -Llibft -Llibmlx_mac -lmlx -framework OpenGL -framework AppKit -lft -o $(NAME)


%.o : %.c
			${CC} $(FLAGS) -c $< -o $@

clean:
			${RM} ${OBJS} ${BOBJS} *.out
			make -C libft clean

fclean:		clean
			$(RM) -rf $(NAME)
			make -C libft fclean

re:			fclean all
norm:
			norminettev2 $(SRCS)
			norminettev2 $(HEADER)
			norminettev2 libft/*.c

.PHONY:		all clean fclean re norm