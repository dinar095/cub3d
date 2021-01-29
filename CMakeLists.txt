cmake_minimum_required(VERSION 3.17)
project(desausag C)

set(CMAKE_C_STANDARD 99)

file(GLOB LIBFILES libft/*.c)
add_library(LibFT STATIC ${LIBFILES})
add_executable(desausag main.c parser/parser.c parser/srcs/ft_header.c parser/gnl/get_next_line.c)
target_link_libraries(desausag LibFT)
target_link_libraries(desausag ${CMAKE_SOURCE_DIR}/minilibx/libmlx.a)
target_link_libraries(desausag "-framework OpenGL")
target_link_libraries(desausag "-framework Appkit")
