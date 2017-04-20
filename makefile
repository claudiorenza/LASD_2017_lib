# the compiler to use
CC      = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CCFLAGS = -g -Wall
RM      = rm -rf

SRC = io/random.c \
	io/io.c \
	stack/stack.c \
	stack/stack_func.c

OBJ = $(SRC:.c=.o)

default: all

all: $(OBJ)
	$(CC) $(CCFLAGS) $(SRC) -o stackApp main.c
	@echo "Build complete"
	
clean:
	$(RM) *.dSYM stack/*.o *.o stackApp
	@echo "Clean complete"
