cmake_minimum_required(VERSION 3.11)
project(chex)

add_subdirectory(external/ftxui)

add_executable(chex src/main.cpp)

target_link_libraries(chex 
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)

