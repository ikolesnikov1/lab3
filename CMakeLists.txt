# cmake_minimum_required(VERSION <specify CMake version here>)
project(krestiki_noliki)

set(CMAKE_CXX_STANDARD 17)

add_executable(krestiki_noliki main.cpp Game.cpp Game.h WrongMove.h Context.h Model.cpp Viewer.cpp Controller.cpp Human.cpp Human.h Player.h AI.cpp AI.h)