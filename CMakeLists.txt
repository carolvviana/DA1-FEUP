cmake_minimum_required(VERSION 3.10)
project(Projeto_DA_1)
set(CMAKE_CXX_STANDARD 14)

#enable sanitizers
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fno-omit-frame-pointer")
#set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fno-omit-frame-pointer")

add_executable(
        Projeto_DA_1
        main.cpp

        src/Menu.cpp src/Menu.h
        src/Railway.cpp src/Railway.h
        src/VertexEdge.cpp src/VertexEdge.h
        src/Graph.h src/Graph.cpp
)

