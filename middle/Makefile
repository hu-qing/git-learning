include ../Makefile.bas

LIB_TARG = libmiddle.a

LIB_OBJS = middle.o

$(LIB_TARG): $(LIB_OBJS)
	$(AR) $(ARPARAM) $@ $(LIB_OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

clean:
	rm -f $(LIB_OBJS) $(LIB_TARG)
