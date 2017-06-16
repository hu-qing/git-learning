ROOTPATH = /home/userx/SHIELD

INCLUDEPATH = $(ROOTPATH)

LIB_TARG = libcore.a

LIB_OBJS = core.o addvol.o bizover.o command.o cutvol.o login.o logout.o ping.o qry.o

$(LIB_TARG): $(LIB_OBJS)
	ar -ruc $@ $(LIB_OBJS)
	ranlib $@

%.o: %.c
	gcc -g -I$(ROOTPATH) -c $<


clean:
	rm -f $(LIB_OBJS) $(LIB_TARG)
