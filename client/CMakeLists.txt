cmake_minimum_required(VERSION 3.16)
project(uchat_gui C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)
include_directories(resources/framework/include/jansson)

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "inc/*.h")

add_executable(uchat_gui src/main.c resources/framework/include/jansson/jansson.h resources/framework/include/jansson/jansson_config.h)

target_link_libraries(uchat_gui -L/Users/dushakov/.brew/Cellar/gtk+3/3.24.23/lib -L/Users/dushakov/.brew/Cellar/pango/1.46.2/lib -L/Users/dushakov/.brew/Cellar/harfbuzz/2.7.2/lib -L/Users/dushakov/.brew/Cellar/atk/2.36.0/lib -L/Users/dushakov/.brew/Cellar/cairo/1.16.0_3/lib -L/Users/dushakov/.brew/Cellar/gdk-pixbuf/2.40.0_1/lib -L/Users/dushakov/.brew/Cellar/glib/2.66.0/lib -L/Users/dushakov/.brew/opt/gettext/lib -lgtk-3 -lgdk-3 -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,CoreGraphics -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl  -L${CMAKE_SOURCE_DIR}/resources/framework/lib/jansson/ -ljansson)
target_compile_options(uchat_gui PRIVATE -I/Users/dushakov/.brew/Cellar/libffi/3.3/include -I/Users/dushakov/.brew/Cellar/gtk+3/3.24.23/include/gtk-3.0 -I/Users/dushakov/.brew/Cellar/glib/2.66.0/include/gio-unix-2.0 -I/Users/dushakov/.brew/Cellar/cairo/1.16.0_3/include/cairo -I/Users/dushakov/.brew/Cellar/libepoxy/1.5.4_1/include -I/Users/dushakov/.brew/Cellar/pango/1.46.2/include/pango-1.0 -I/Users/dushakov/.brew/Cellar/fribidi/1.0.10/include/fribidi -I/Users/dushakov/.brew/Cellar/harfbuzz/2.7.2/include/harfbuzz -I/Users/dushakov/.brew/Cellar/graphite2/1.3.14/include -I/Users/dushakov/.brew/Cellar/atk/2.36.0/include/atk-1.0 -I/Users/dushakov/.brew/Cellar/cairo/1.16.0_3/include/cairo -I/Users/dushakov/.brew/Cellar/pixman/0.40.0/include/pixman-1 -I/Users/dushakov/.brew/Cellar/fontconfig/2.13.1/include -I/Users/dushakov/.brew/opt/freetype/include/freetype2 -I/Users/dushakov/.brew/Cellar/libpng/1.6.37/include/libpng16 -I/Users/dushakov/.brew/Cellar/gdk-pixbuf/2.40.0_1/include/gdk-pixbuf-2.0 -I/Users/dushakov/.brew/Cellar/glib/2.66.0/include -I/Users/dushakov/.brew/Cellar/glib/2.66.0/include/glib-2.0 -I/Users/dushakov/.brew/Cellar/glib/2.66.0/lib/glib-2.0/include -I/Users/dushakov/.brew/opt/gettext/include -I/Users/dushakov/.brew/Cellar/pcre/8.44/include)
