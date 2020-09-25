cmake_minimum_required(VERSION 3.16)
project(UCHAT C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)
include_directories(resources/framework/include/jansson)

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "inc/*.h")

add_executable(UCHAT src/main.c resources/framework/include/jansson/jansson.h resources/framework/include/jansson/jansson_config.h)

#target_compile_options(UCHAT PRIVATE -I${CMAKE_SOURCE_DIR}/resources/framework/include/jansson)
target_link_libraries(UCHAT -L${CMAKE_SOURCE_DIR}/resources/framework/lib/jansson/ -ljansson)

#target_compile_options(UCHAT PRIVATE
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/libffi
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/gtk-3.0
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/gio-unix-2.0
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/cairo
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/libepoxy
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/pango-1.0
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/fribidi
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/harfbuzz
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/graphite2
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/atk
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/pixman
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/fontconfig
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/freetype2
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/libpng16
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/gdk-pixbuf-2.0
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/glib/2.66.0/include
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/glib/2.66.0/include/glib-2.0
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/glib/2.66.0/lib/glib-2.0/include
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/gettext
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/pcre
#        -I${CMAKE_SOURCE_DIR}/resources/framework/include/jansson
#        )
#
#target_link_libraries(UCHAT
#        -L${CMAKE_SOURCE_DIR}/resources/framework/lib/gtk+3
#        -L${CMAKE_SOURCE_DIR}/resources/framework/lib/pango
#        -L${CMAKE_SOURCE_DIR}/resources/framework/lib/harfbuzz
#        -L${CMAKE_SOURCE_DIR}/resources/framework/lib/atk
#        -L${CMAKE_SOURCE_DIR}/resources/framework/lib/cairo
#        -L${CMAKE_SOURCE_DIR}/resources/framework/lib/gdk-pixbuf
#        -L${CMAKE_SOURCE_DIR}/resources/framework/lib/glib
#        -L${CMAKE_SOURCE_DIR}/resources/framework/lib/gettext
#        -L${CMAKE_SOURCE_DIR}/resources/framework/lib/jansson
#        -lgtk-3 -lgdk-3 -Wl -Wl -Wl -ljansson
#        -lpangocairo-1.0 -lpango-1.0
#        -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo
#        -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl)
