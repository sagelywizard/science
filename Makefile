CFLAGS=--std=c99 -pedantic -Wall -I/usr/local/lib/erlang/erts-5.8.4/include/ -undefined dynamic_lookup -shared -lgsl -lblas -o science.so

all:
	gcc $(CFLAGS) double_list.c science.c

clean:
	rm science.so
