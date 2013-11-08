
CC 	 = gcc
DEBUGGING= -DDEBUG -g
CFLAGS 	 = -Wall $(DEBUGGING) 
LDFLAGS  = 

SOURCES  = rnode.c rlinked_list.c rbinary_tree.c
OBJS 	 = $(SOURCES:.c=.o)

INC_PATH = -I./ 
LD_PATH  = -L./ 

.PHONY: clean
    
all: clean 

test: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INC_PATH) $(LD_PATH) $^ examples/example_bst.c -o examples/example_bst
	@$(RM) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(INC_PATH) $(LD_PATH) -c $<

clean:
	@$(RM) $(OBJS)
