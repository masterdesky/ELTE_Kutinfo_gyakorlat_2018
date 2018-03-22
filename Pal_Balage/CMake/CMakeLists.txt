cmake_minimum_required(VERSION 2.8.12)

# A projekt neve
project(cmaketest LANGUAGES CXX)

# Mi van ha megváltozik a neve a projektnek?
add_executable(${PROJECT_NAME} cmaketest.cpp)
