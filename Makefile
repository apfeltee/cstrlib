
# name of our library
libname = libcstr.a

# source files
exesrc  = test.c
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)

# include directories
includes = -Iinclude

# compiler flags
CFLAGS = -g -Wall -Wextra $(includes)

# linker flags
LDFLAGS = -g -lm

# compiler
CC = cc

.SUFFIXES: .c

default: $(libname)

$(libname): $(objects)
	ar rcs $(libname) $(objects)
	ranlib $(libname)

clean:
	$(RM) $(objects)

dist-clean: clean
	$(RM) $(libname)

rebuild: dist-clean default

help:
	@echo "supported commands"
	@echo "   'help'          show this help"
	@echo "   'default'       build '$(libname)' (default operation)"
	@echo "   'clean'         delete generated object files"
	@echo "   'dist-clean'    invoke 'clean', and delete '$(libname)' as well"
	@echo "   'rebuild'       invoke 'dist-clean', and then 'default'"

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@