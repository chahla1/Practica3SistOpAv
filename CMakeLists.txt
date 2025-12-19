cmake_minimum_required(VERSION 3.20)
project(PracticaSockets C)

set(CMAKE_C_STANDARD 11)


add_executable(servidor_basico servidorOpAlgebraicas.c)


add_executable(servidor_procesos servidorProcTCP.c)


add_executable(servidor_hebras servidorHebTCP.c)

target_link_libraries(servidor_hebras pthread)

add_executable(cliente cliente.c
        servidorProcTCP.c
        servidorHebTCP.c)
