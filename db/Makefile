OBJS = tables_init.o
CC = gcc
LFLAGS = -Wall -g
LIBS = -L./libs -lsqlite3
INCLUDE = -I./include
EXE = tables_init


$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE) $(LIBS)

$(OBJS) : tables_init.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $<


.PHONY: clean

clean:
	rm -f $(OBJS)
