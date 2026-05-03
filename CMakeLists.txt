cmake_minimum_required(VERSION 3.11)
project(chex)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/ftxui)

set(LIB_SOURCES
    src/buffer.cpp
    src/cursor.cpp
    src/view.cpp
    src/tui.cpp
    src/controller.cpp
)

set(LIB_HEADERS
    include/buffer.hpp
    include/cursor.hpp
    include/view.hpp
    include/tui.hpp
    include/controller.hpp
    include/viewport.hpp
)

add_library(Lib STATIC ${LIB_SOURCES})

target_sources(Lib PUBLIC FILE_SET HEADERS BASE_DIRS include FILES ${LIB_HEADERS})

target_include_directories(Lib PUBLIC include)
target_link_libraries(Lib PUBLIC ftxui::screen ftxui::dom ftxui::component)

add_executable(chex src/main.cpp)

target_link_libraries(chex PRIVATE Lib)

