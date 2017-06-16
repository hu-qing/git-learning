
LIB_TARG = libframe.a

LIB_OBJS = frame.o handler.o net.o protocol.o queue.o thread.o

$(LIB_TARG): $(LIB_OBJS)
	ar -ruc $@ $(LIB_OBJS)
	ranlib $@

%.o:%c
	gcc -g -Wall -I$(ROOTPATH) -c $<

clean:
	rm -f $(LIB_OBJS) $(LIB_TARG)
