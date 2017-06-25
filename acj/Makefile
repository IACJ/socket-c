# Create By IACJ - 2017/6/24
#
# My First Makefile

PROGS =  demo_client demo_server ACJ_client.excute ACJ_server.excute hello

all: ${PROGS}

ACJ_client.excute: ACJ_client.c
	gcc ACJ_client.c -o ACJ_client.excute

ACJ_server.excute: ACJ_server.c
	gcc ACJ_server.c -o ACJ_server.excute

hello: hello.c
	gcc hello.c -o hello

demo_client: demo_client.c
	gcc $@.c -o $@

demo_server: demo_server.c
	gcc $@.c -o $@

clean:
	rm -rf ${PROGS} *.o