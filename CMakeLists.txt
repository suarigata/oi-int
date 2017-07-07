cmake_minimum_required(VERSION 3.5)
project(openisa-dbt)

set(CMAKE_CXX_FLAGS "-Ofast -Werror -Wall -Wextra -Wno-unused-function -std=c++17 -fno-rtti -flto -DNDEBUG")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Ofast -flto")

include_directories(include)

add_subdirectory(arglib)

add_library(dbt interpreter.cpp machine.cpp syscall.cpp)

add_executable(oi-int main.cpp)

install(TARGETS oi-int RUNTIME DESTINATION bin)

target_link_libraries(oi-int
  dbt 
  arglib 
  z
)
