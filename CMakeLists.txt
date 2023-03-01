cmake_minimum_required(VERSION 3.22)
project(vending_machine)

set(CMAKE_CXX_STANDARD 14)

add_executable(vending_machine main.cpp Product.h vendingMachine.cpp vendingMachine.h Coin.h Coin.cpp)
