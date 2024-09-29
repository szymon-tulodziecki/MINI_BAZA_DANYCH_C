cmake_minimum_required(VERSION 3.28)
project(mini_baza_danych C)

set(CMAKE_C_STANDARD 11)

add_executable(mini_baza_danych main.c
        funkcje.c
        funkcje.h)
