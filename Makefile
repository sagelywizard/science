CFLAGS=-I/usr/local/lib/erlang/erts-5.8.4/include/ -undefined dynamic_lookup -shared -lgsl -lblas -o science.so

all:
	gcc $(CFLAGS) science.c

clean:
	rm science.so
