cmake_minimum_required(VERSION 3.16)
project(uchat_gui C)

set(CMAKE_C_STANDARD 11)

include_directories(client/inc)
include_directories(server/inc)
include_directories(server/resources/libmx/inc)
include_directories(client/resources/framework/jansson/inc)
include_directories(client/resources/framework/macros.h)
include_directories(client/resources/framework/cmc)
include_directories(client/resources/framework/cmc/cmc)
include_directories(client/resources/framework/cmc/cor)
include_directories(client/resources/framework/cmc/ext)
include_directories(client/resources/framework/cmc/utl)

file(GLOB_RECURSE CLIENT_SRC RELATIVE ${CMAKE_SOURCE_DIR} "client/src/*.c")
file(GLOB_RECURSE CLIENT_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "client/inc/*.h")

file(GLOB_RECURSE SERVER_SRC RELATIVE ${CMAKE_SOURCE_DIR} "server/src/*.c")
file(GLOB_RECURSE SERVER_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "server/inc/*.h")

file(GLOB_RECURSE LIB_SRC RELATIVE ${CMAKE_SOURCE_DIR} "server/resources/libmx/src/*.c")
file(GLOB_RECURSE LIB_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "server/resources/libmx/inc/*.h")

file(GLOB_RECURSE CMC_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "client/resources/framework/cmc/*.h")

add_executable(uchat_gui ${CLIENT_SRC} ${CLIENT_HEADERS}
        ${LIB_SRC} ${LIB_HEADERS} ${CMC_HEADERS}
        client/resources/framework/jansson/inc/jansson.h
        client/resources/framework/jansson/inc/jansson_config.h
        client/resources/framework/macros.h/macros.h)

#target_link_libraries(uchat_gui -L/Users/dushakov/.brew/Cellar/gtk+3/3.24.23/lib
#        -L/Users/dushakov/.brew/Cellar/pango/1.46.2/lib
#        -L/Users/dushakov/.brew/Cellar/harfbuzz/2.7.2/lib
#        -L/Users/dushakov/.brew/Cellar/atk/2.36.0/lib
#        -L/Users/dushakov/.brew/Cellar/cairo/1.16.0_3/lib
#        -L/Users/dushakov/.brew/Cellar/gdk-pixbuf/2.40.0_1/lib
#        -L/Users/dushakov/.brew/Cellar/glib/2.66.0/lib
#        -L/Users/dushakov/.brew/opt/gettext/lib
#        -L${CMAKE_SOURCE_DIR}/client/resources/framework/jansson/
#        -lgtk-3 -lgdk-3 -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,CoreGraphics
#        -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0
#        -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -ljansson)
#target_compile_options(uchat_gui PRIVATE -I/Users/dushakov/.brew/Cellar/libffi/3.3/include
#        -I/Users/dushakov/.brew/Cellar/gtk+3/3.24.23/include/gtk-3.0
#        -I/Users/dushakov/.brew/Cellar/glib/2.66.0/include/gio-unix-2.0
#        -I/Users/dushakov/.brew/Cellar/cairo/1.16.0_3/include/cairo
#        -I/Users/dushakov/.brew/Cellar/libepoxy/1.5.4_1/include
#        -I/Users/dushakov/.brew/Cellar/pango/1.46.2/include/pango-1.0
#        -I/Users/dushakov/.brew/Cellar/fribidi/1.0.10/include/fribidi
#        -I/Users/dushakov/.brew/Cellar/harfbuzz/2.7.2/include/harfbuzz
#        -I/Users/dushakov/.brew/Cellar/graphite2/1.3.14/include
#        -I/Users/dushakov/.brew/Cellar/atk/2.36.0/include/atk-1.0
#        -I/Users/dushakov/.brew/Cellar/cairo/1.16.0_3/include/cairo
#        -I/Users/dushakov/.brew/Cellar/pixman/0.40.0/include/pixman-1
#        -I/Users/dushakov/.brew/Cellar/fontconfig/2.13.1/include
#        -I/Users/dushakov/.brew/opt/freetype/include/freetype2
#        -I/Users/dushakov/.brew/Cellar/libpng/1.6.37/include/libpng16
#        -I/Users/dushakov/.brew/Cellar/gdk-pixbuf/2.40.0_1/include/gdk-pixbuf-2.0
#        -I/Users/dushakov/.brew/Cellar/glib/2.66.0/include
#        -I/Users/dushakov/.brew/Cellar/glib/2.66.0/include/glib-2.0
#        -I/Users/dushakov/.brew/Cellar/glib/2.66.0/lib/glib-2.0/include
#        -I/Users/dushakov/.brew/opt/gettext/include -I/Users/dushakov/.brew/Cellar/pcre/8.44/include)

# Jenia
target_link_libraries(uchat_gui -L/Users/yksonzenko/.brew/Cellar/gtk+3/3.24.23/lib
        -L/Users/yksonzenko/.brew/Cellar/pango/1.46.2/lib
        -L/Users/yksonzenko/.brew/Cellar/harfbuzz/2.7.2/lib
        -L/Users/yksonzenko/.brew/Cellar/atk/2.36.0/lib
        -L/Users/yksonzenko/.brew/Cellar/cairo/1.16.0_3/lib
        -L/Users/yksonzenko/.brew/Cellar/gdk-pixbuf/2.40.0_1/lib
        -L/Users/yksonzenko/.brew/Cellar/glib/2.66.0/lib
        -L/Users/yksonzenko/.brew/opt/gettext/lib
        -L${CMAKE_SOURCE_DIR}/client/resources/framework/jansson/
        -lgtk-3 -lgdk-3 -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,CoreGraphics
        -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0
        -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -ljansson)

target_compile_options(uchat_gui PRIVATE -I/Users/yksonzenko/.brew/Cellar/libffi/3.3/include -I/Users/yksonzenko/.brew/Cellar/gtk+3/3.24.23/include/gtk-3.0 -I/Users/yksonzenko/.brew/Cellar/glib/2.66.0/include/gio-unix-2.0 -I/Users/yksonzenko/.brew/Cellar/cairo/1.16.0_3/include/cairo -I/Users/yksonzenko/.brew/Cellar/libepoxy/1.5.4_1/include -I/Users/yksonzenko/.brew/Cellar/pango/1.46.2/include/pango-1.0 -I/Users/yksonzenko/.brew/Cellar/fribidi/1.0.10/include/fribidi -I/Users/yksonzenko/.brew/Cellar/harfbuzz/2.7.2/include/harfbuzz -I/Users/yksonzenko/.brew/Cellar/graphite2/1.3.14/include -I/Users/yksonzenko/.brew/Cellar/atk/2.36.0/include/atk-1.0 -I/Users/yksonzenko/.brew/Cellar/cairo/1.16.0_3/include/cairo -I/Users/yksonzenko/.brew/Cellar/pixman/0.40.0/include/pixman-1 -I/Users/yksonzenko/.brew/Cellar/fontconfig/2.13.1/include -I/Users/yksonzenko/.brew/opt/freetype/include/freetype2 -I/Users/yksonzenko/.brew/Cellar/libpng/1.6.37/include/libpng16 -I/Users/yksonzenko/.brew/Cellar/gdk-pixbuf/2.40.0_1/include/gdk-pixbuf-2.0 -I/Users/yksonzenko/.brew/Cellar/glib/2.66.0/include -I/Users/yksonzenko/.brew/Cellar/glib/2.66.0/include/glib-2.0 -I/Users/yksonzenko/.brew/Cellar/glib/2.66.0/lib/glib-2.0/include -I/Users/yksonzenko/.brew/opt/gettext/include -I/Users/yksonzenko/.brew/Cellar/pcre/8.44/include)

add_executable(uchat_server ${SERVER_SRC} ${SERVER_HEADERS} ${LIB_SRC} ${LIB_HEADERS})
target_link_libraries(uchat_server -L${CMAKE_SOURCE_DIR}/server/resources/framework/jansson/ -ljansson -lsqlite3 -lpthread)
