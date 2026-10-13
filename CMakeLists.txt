cmake_minimum_required(VERSION 4.3)
project(blackjack-cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(blackjack-cpp src/main.cpp
        src/Card.cpp
        src/Card.h
        src/Deck.cpp
        src/Deck.h
        src/Random.h)
