add_definitions (-std=c++14 -O0)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library (ObjSDL_events
    event.cc event.hh
    window_event.cc window_event.hh
    keyboard_event.cc keyboard_event.hh
    mouse_event.cc mouse_event.hh
    joystick_event.cc joystick_event.hh
    controller_event.cc controller_event.hh
    touch_event.cc touch_event.hh
    various_events.cc various_events.hh
)

include (../cmake/FindSDL2.cmake)

find_package (Boost COMPONENTS system REQUIRED)
find_package (SDL2 REQUIRED)

include_directories (${SDL2_INCLUDE_DIR})
include_directories (${Boost_INCLUDE_DIRS})

install (TARGETS ObjSDL_events DESTINATION bin)
