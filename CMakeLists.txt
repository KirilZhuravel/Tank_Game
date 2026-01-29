cmake_minimum_required(VERSION 4.0)
project(hogwards C)

set(CMAKE_C_STANDARD 11)

add_executable(hogwards main.c
        tank_game.h
        tank_game.c)
