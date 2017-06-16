ROOTPATH = /home/userx/SHIELD

INCLUDEPATH = $(ROOTPATH)

LIB_TARG = libmiddle.a

LIB_OBJS = middle.o

$(LIB_TARG): $(LIB_OBJS)
	ar -ruc $@ $(LIB_OBJS)
	ranlib $@

$(LIB_OBJS): middle.c
	gcc -g -Wall -I$(ROOTPATH) -c middle.c

clean:
	rm -f $(LIB_OBJS) $(LIB_TARG)
