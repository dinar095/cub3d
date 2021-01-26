cmake_minimum_required(VERSION 3.17)
project(desausag C)

set(CMAKE_C_STANDARD 99)


add_executable(desausag main.c )
target_link_libraries(desausag "~/Documents/cub3d/desausag/libft/libft.a")
target_link_libraries(desausag "~/Documents/cub3d/desausag/minilibx/libmlx.a")
target_link_libraries(desausag "-framework OpenGL")
target_link_libraries(desausag "-framework Appkit")
add_executable(parser parser/parser.c parser/gnl/get_next_line.c parser/gnl/get_next_line_utils.c)
target_link_libraries(parser "~/Documents/cub3d/desausag/libft/libft.a")