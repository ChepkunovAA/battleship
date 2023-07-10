cmake_minimum_required(VERSION 3.0)
project(battleship)

set (CMAKE_CXX_STANDARD 11)
set(HEADERS_DIR "${battleship_SOURCE_DIR}/includes")
set(SRC_DIR "${battleship_SOURCE_DIR}/src")

add_executable( run
  main.cpp
  ./sourse/App.cpp
  ./sourse/Interface.cpp
  ./sourse/Players.cpp
  ./sourse/Game.cpp
  ./sourse/Model.cpp
  ./sourse/Ships.cpp
)

target_include_directories(run PUBLIC ${battleship_SOURCE_DIR}/includes)

