# the compiler to use
CC      = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CCFLAGS = -g -Wall
RM      = rm -rf

SRC_IO = io/random.c \
	io/io.c

SRC_S = stack/stack.c \
	stack/stack_func.c

SRC_Q = queue/queue.c \
	queue/queue_func.c

SRC = $(SRC_IO) $(SRC_S) $(SRC_Q)


OBJ_IO = $(SRC_IO:.c=.o)

OBJ_S = $(SRC_S:.c=.o)

OBJ_Q = $(SRC_Q:.c=.o)

OBJ = $(SRC:.c=.o)

default: all

all: $(OBJ)
	$(CC) $(CCFLAGS) $(SRC) -o mainLib main.c
	@echo "Build complete"
	
stack: $(OBJ_IO) $(OBJ_S)
	$(CC) $(CCFLAGS) $(SRC_IO) $(SRC_S) -o stack/stackLib stack/main.c

QUEUE: $(OBJ_IO) $(OBJ_Q)
	$(CC) $(CCFLAGS) $(SRC_IO) $(SRC_Q) -o queue/queueLib queue/main.c

clean:
	$(RM) *.dSYM stack/*.o queue/*.o io/*.o *.o mainLib
	@echo "Clean complete"

clean_stack:
	$(RM) *.dSYM stack/*.o io/*.o *.o stack/stackLib
	@echo "Clean complete"
	
clean_queue:
	$(RM) *.dSYM queue/*.o io/*.o *.o queue/queueLib
	@echo "Clean complete"