project(termollo)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

file(GLOB_RECURSE APP_SOURCES piccolo/*.c piccolo/*.h)
add_library(termollo SHARED termollo.c ${APP_SOURCES})
target_link_libraries(termollo ${CURSES_LIBRARIES})
