CC=gcc
CFLAGS=-c -ggdb -Wall -fPIC -Wextra -Wpedantic
LDFLAGS=-shared
LIBS=libarraylist.so liblinkedlist.so libhashtable.so libstack.so libhmalloc.so

all: $(LIBS) testsuite

arraylist.o: arraylist.c
	$(CC) $(CFLAGS) $< -o $@

linkedlist.o: linkedlist.c
	$(CC) $(CFLAGS) $< -o $@

hashtable.o: hashtable.c
	$(CC) $(CFLAGS) $< -o $@

stack.o: stack.c
	$(CC) $(CFLAGS) $< -o $@

hmalloc.o: hmalloc.c
	$(CC) $(CFLAGS) $< -o $@

#############################
libarraylist.so: arraylist.o
	$(CC) $(LDFLAGS) $< -o $@

liblinkedlist.so: linkedlist.o
	$(CC) $(LDFLAGS) $< -o $@

libhashtable.so: hashtable.o
	$(CC) $(LDFLAGS) $< -o $@

libstack.so: stack.o
	$(CC) $(LDFLAGS) $< -o $@

libhmalloc.so: hmalloc.o
	$(CC) $(LDFLAGS) $< -o $@

##############################
testsuite: testsuite.c $(LIBS)
	$(CC) $< -o $@ -L. -larraylist -llinkedlist -lhashtable -lstack -lhmalloc
clean:
	rm -f *.o *.so testsuite a.out
