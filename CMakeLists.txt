project(Game)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(src SRC_LIST)
aux_source_directory(src/menu SRC_LIST)

#QTCreator precisa da lista de headers para adicionar ao projeto.
FILE(GLOB_RECURSE HEADER_LIST "include/*.h")

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-c++11-narrowing -Wno-gnu-array-member-paren-init -Wno-unused-variable -Wno-overloaded-virtual -Wno-reorder -Wno-macro-redefined -Wno-sign-compare -Wno-unused-private-field -ggdb -O0 ${CMAKE_CXX_FLAGS}")
include_directories(${PROJECT_SOURCE_DIR}/include)

if (UNIX)
    include_directories("/usr/include/SDL2" "/usr/local/Cellar/sdl2/2.0.5/include/SDL2" "/usr/local/Cellar/sdl2_image/2.0.1_3/include/SDL2" "/usr/local/Cellar/sdl2_mixer/2.0.1_1/include/SDL2" "/usr/local/Cellar/sdl2_ttf/2.0.14/include/SDL2")
    link_directories("/usr/local/lib")
endif (UNIX)

link_libraries(SDL2main SDL2_image SDL2_ttf SDL2_mixer SDL2)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER_LIST})
