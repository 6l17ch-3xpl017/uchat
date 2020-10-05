# name of binary
NAME		= uchat

# main dir for source files
SRC_DIR		= src/
# main dir for obj files
OBJ_DIR		= obj/
# main dir for header files
INC_DIR		= inc/

# main dir for jansson files
J_INC_DIR   = resources/framework/jansson/inc/

# list of subdirs in src/
DIRS		= $(notdir $(wildcard $(SRC_DIR)*))
# list of only source C-files without extansions
FILES		= $(foreach dir, $(DIRS), $(basename $(wildcard \
			  $(SRC_DIR)$(dir)/*.c)))
# adding extansions .c to FILES
SRC			= $(FILES:%=%.c)
# adding extansions .o to FILES
OBJ			= $(SRC:src/%.c=$(OBJ_DIR)%.o)
# list of header files
INC_H		= $(wildcard $(INC_DIR)*.h)

# list of jansson header files
J_INC_H		= $(wildcard $(J_INC_DIR)*.h)

J_BIN = resources/framework/jansson/libjansson.a

# main dir with any libraries
LIB_DIR		= ./resources
# list of all names of libraries in LIB_DIR
LIB_LIST	= libmx
# make path to library ../libs/<lib_name>/
LIB_DIRS	= $(foreach libdirs, $(LIB_LIST), $(LIB_DIR)/$(libdirs)/)
# make path to ../libs/<lib_name>/<lib_name>.a
LIB_BIN		= $(join $(LIB_DIRS), $(addsuffix .a, $(LIB_LIST)))
# make path to ../libs/<lib_name>/inc
LIB_INC		= $(addsuffix $(INC_DIR), $(LIB_DIRS))


# compiler
CC			= clang
# general flags
GFLAGS		= -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic -g
# specific flags
CFLAGS		= -lsqlite3 -lpthread $(shell pkg-config --cflags gtk+-3.0)

#GTK_IFLAGS		= -I/Users/dushakov/.brew/Cellar/libffi/3.3/include -I/Users/dushakov/.brew/Cellar/gtk+3/3.24.23/include/gtk-3.0 -I/Users/dushakov/.brew/Cellar/glib/2.66.0/include/gio-unix-2.0 -I/Users/dushakov/.brew/Cellar/cairo/1.16.0_3/include/cairo -I/Users/dushakov/.brew/Cellar/libepoxy/1.5.4_1/include -I/Users/dushakov/.brew/Cellar/pango/1.46.2/include/pango-1.0 -I/Users/dushakov/.brew/Cellar/fribidi/1.0.10/include/fribidi -I/Users/dushakov/.brew/Cellar/harfbuzz/2.7.2/include/harfbuzz -I/Users/dushakov/.brew/Cellar/graphite2/1.3.14/include -I/Users/dushakov/.brew/Cellar/atk/2.36.0/include/atk-1.0 -I/Users/dushakov/.brew/Cellar/cairo/1.16.0_3/include/cairo -I/Users/dushakov/.brew/Cellar/pixman/0.40.0/include/pixman-1 -I/Users/dushakov/.brew/Cellar/fontconfig/2.13.1/include -I/Users/dushakov/.brew/opt/freetype/include/freetype2 -I/Users/dushakov/.brew/Cellar/libpng/1.6.37/include/libpng16 -I/Users/dushakov/.brew/Cellar/gdk-pixbuf/2.40.0_1/include/gdk-pixbuf-2.0 -I/Users/dushakov/.brew/Cellar/glib/2.66.0/include -I/Users/dushakov/.brew/Cellar/glib/2.66.0/include/glib-2.0 -I/Users/dushakov/.brew/Cellar/glib/2.66.0/lib/glib-2.0/include -I/Users/dushakov/.brew/opt/gettext/include -I/Users/dushakov/.brew/Cellar/pcre/8.44/include
#GTK_LFLAGS		= -L/Users/dushakov/.brew/Cellar/gtk+3/3.24.23/lib -L/Users/dushakov/.brew/Cellar/pango/1.46.2/lib -L/Users/dushakov/.brew/Cellar/harfbuzz/2.7.2/lib -L/Users/dushakov/.brew/Cellar/atk/2.36.0/lib -L/Users/dushakov/.brew/Cellar/cairo/1.16.0_3/lib -L/Users/dushakov/.brew/Cellar/gdk-pixbuf/2.40.0_1/lib -L/Users/dushakov/.brew/Cellar/glib/2.66.0/lib -L/Users/dushakov/.brew/opt/gettext/lib -lgtk-3 -lgdk-3 -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,CoreGraphics -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl
# folder with header files
IFLAGS		= $(addprefix -I , $(LIB_INC) $(INC_DIR) $(J_INC_DIR))
CMC_I 		= -I/Users/dushakov/CLionProjects/uchat_test/client/resources/framework/cmc

COMPILE		= $(CC) $(GFLAGS) $(IFLAGS) $(CMC_I) $(CFLAGS) $(LIB_BIN) $(J_BIN)
MAKE_M		= make -sf Makefile -C
MKDIR		= mkdir -p
RM			= /bin/rm -rf

# checking if libs are up to date
all: $(NAME)

# LIB_BIN for libs dependency
$(NAME): $(LIB_LIST) $(OBJ_DIR) $(OBJ)
	@$(COMPILE) $(OBJ) -lmx $(shell pkg-config --libs gtk+-3.0) -o $(NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(LIB_BIN): $(LIB_LIST)

# make for all libs
$(LIB_LIST): $(LIB_DIRS)
	@$(MAKE_M) $(LIB_DIR)/$@

# make dirs for obj files
$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(DIRS), $@/$(dir))

# compiling obj files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_H) $(LIB_BIN)
	@$(COMPILE) -o $@ -c $<
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRC_DIR)/%.c=%)"

clean:
	@$(MAKE_M) $(LIB_DIR)/$(LIB_LIST) $@
	@$(RM) $(OBJ_DIR)
	@printf "obj in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(MAKE_M) $(LIB_DIR)/$(LIB_LIST) $@
	@$(RM) $(OBJ_DIR) $(NAME)
	@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all clean uninstall reinstall $(LIB_LIST)
