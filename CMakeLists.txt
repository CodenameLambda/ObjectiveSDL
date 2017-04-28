cmake_minimum_required (VERSION 2.8)

add_definitions (-std=c++14 -O3 -Os)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library (ObjSDL
    color_names.cc color.cc color.hh  # color_names provides the values for the named colors
    cursor.cc cursor.hh
    clock.cc clock.hh
    short_types.cc short_types.hh  # header only
    clipboard.cc clipboard.hh
    geometry.hh geometry.cc  # header only
    version.cc version.hh
)

include (cmake/FindSDL2.cmake)

find_package (Boost COMPONENTS system REQUIRED)
find_package (SDL2 REQUIRED)

include_directories (${SDL2_INCLUDE_DIR})

link_directories (${Boost_LIBRARY_DIRS})

if (Boost_FOUND)
    include_directories (${Boost_INCLUDE_DIRS})
    target_link_libraries (ObjSDL ${Boost_SYSTEM_LIBRARY})
endif ()

target_link_libraries (ObjSDL ${SDL2_LIBRARY})

install (TARGETS ObjSDL DESTINATION bin)
