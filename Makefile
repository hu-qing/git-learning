ROOTPATH = /home/userx/SHIELD

SVR_NAME = shield
OBJS = shield.o
all: libs $(SVR_NAME)

LIBS = -L$(ROOTPATH)/frame -lframe \
       -L$(ROOTPATH)/middle -lmiddle \
       -L$(ROOTPATH)/core -lcore \
	   -lpthread

libs:
	@make -C frame
	@make -C middle
	@make -C core

$(SVR_NAME): $(OBJS)
	gcc -Wall $(OBJS) $(LIBS) -o $(SVR_NAME)

%.o: %.c
	gcc -g -Wall -I$(ROOTPATH) -c $<

clean:
	rm -f $(OBJS) $(SVR_NAME)
	@make -C frame  clean
	@make -C middle clean
	@make -C core   clean
