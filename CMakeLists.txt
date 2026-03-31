cmake_minimum_required(VERSION 3.11)
project(chex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCE "src/*.cpp")
add_library(Lib STATIC ${SOURCE})

add_subdirectory(external/ftxui)

add_executable(chex test.cpp)

target_link_libraries(chex
    PRIVATE Lib
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)

