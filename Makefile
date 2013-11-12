
CC 	 = gcc
DEBUGGING= -DDEBUG -g
CFLAGS 	 = -Wall $(DEBUGGING) 
LDFLAGS  =

SOURCES  = rnode.c rlinked_list.c rbinary_tree.c
OBJS 	 = $(SOURCES:.c=.o)

INC_PATH = -I./ 
LD_PATH  = -L./ 

LIBNAME = dsrc

TESTDIR	= examples
EXAMPLES= example_ll,example_bst

.PHONY: clean test

define cc-test
$(CC) $(CFLAGS) $(LDFLAGS) $(INC_PATH) $(LD_PATH) -l$(LIBNAME) $< -o $(TESTDIR)/$@
endef

all: clean lib$(LIBNAME).so

lib$(LIBNAME).so: $(OBJS)
	$(CC) -shared -o $@ $^
	@$(RM) $(OBJS)

examples: lib$(LIBNAME).so example_ll example_bst

example_ll: $(TESTDIR)/example_ll.c
	$(cc-test)	

example_bst: $(TESTDIR)/example_bst.c
	$(cc-test)	

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(INC_PATH) $(LD_PATH) -c -fpic $<

clean:
	@$(RM) $(OBJS) lib$(LIBNAME).so $(TESTDIR)/{$(EXAMPLES)}
