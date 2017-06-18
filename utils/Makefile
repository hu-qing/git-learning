include ../Makefile.bas

LIB_TARG = libutils.a
LIB_OBJS = queue.o hash.o array.o


$(LIB_TARG): $(LIB_OBJS)
	$(AR) $(ARPARAM) $@ $(LIB_OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(LIB_OBJS) $(LIB_TARG)
