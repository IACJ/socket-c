# Create By IACJ - 2017/6/24
#
# My First Makefile

PROGS = hello demo_client demo_server

all: ${PROGS}

hello: hello.c
	cc $@.c -o $@

demo_client: demo_client.c
	cc $@.c -o $@

demo_server: demo_server.c
	cc $@.c -o $@

clean:
	rm -rf ${PROGS} *.o