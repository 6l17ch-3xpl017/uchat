cmake_minimum_required(VERSION 3.16)
project(UCHAT C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "inc/*.h")

add_executable(UCHAT ${SRC} ${HEADERS})
target_compile_options(UCHAT PRIVATE
        -I/resources/framework/libffi
        -I/resources/framework/gtk-3.0
        -I/resources/framework/gio-unix-2.0
        -I/resources/framework/cairo
        -I/resources/framework/libepoxy
        -I/resources/framework/pango-1.0
        -I/Users/dushakov/Documents/homebrew/Cellar/fribidi/1.0.10/include/fribidi
        -I/Users/dushakov/Documents/homebrew/Cellar/harfbuzz/2.7.2/include/harfbuzz
        -I/Users/dushakov/Documents/homebrew/Cellar/graphite2/1.3.14/include
        -I/Users/dushakov/Documents/homebrew/Cellar/atk/2.36.0/include/atk-1.0
        -I/Users/dushakov/Documents/homebrew/Cellar/cairo/1.16.0_3/include/cairo
        -I/Users/dushakov/Documents/homebrew/Cellar/pixman/0.40.0/include/pixman-1
        -I/Users/dushakov/Documents/homebrew/Cellar/fontconfig/2.13.1/include
        -I/Users/dushakov/Documents/homebrew/opt/freetype/include/freetype2
        -I/Users/dushakov/Documents/homebrew/Cellar/libpng/1.6.37/include/libpng16
        -I/Users/dushakov/Documents/homebrew/Cellar/gdk-pixbuf/2.40.0_1/include/gdk-pixbuf-2.0
        -I/Users/dushakov/Documents/homebrew/Cellar/glib/2.66.0/include
        -I/Users/dushakov/Documents/homebrew/Cellar/glib/2.66.0/include/glib-2.0
        -I/Users/dushakov/Documents/homebrew/Cellar/glib/2.66.0/lib/glib-2.0/include
        -I/Users/dushakov/Documents/homebrew/opt/gettext/include
        -I/Users/dushakov/Documents/homebrew/Cellar/pcre/8.44/include)
target_link_libraries(UCHAT
        -L/Users/dushakov/Documents/homebrew/Cellar/gtk+3/3.24.23/lib
        -L/Users/dushakov/Documents/homebrew/Cellar/pango/1.46.2/lib
        -L/Users/dushakov/Documents/homebrew/Cellar/harfbuzz/2.7.2/lib
        -L/Users/dushakov/Documents/homebrew/Cellar/atk/2.36.0/lib
        -L/Users/dushakov/Documents/homebrew/Cellar/cairo/1.16.0_3/lib
        -L/Users/dushakov/Documents/homebrew/Cellar/gdk-pixbuf/2.40.0_1/lib
        -L/Users/dushakov/Documents/homebrew/Cellar/glib/2.66.0/lib
        -L/Users/dushakov/Documents/homebrew/opt/gettext/lib
        -lgtk-3 -lgdk-3 -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,
        -framework,CoreGraphics -lpangocairo-1.0 -lpango-1.0
        -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo
        -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl)
