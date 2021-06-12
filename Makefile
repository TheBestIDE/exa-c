objs = main.o grid.o fexdet.o syscall.o list.o
cc = gcc

exa : $(objs)
	@cc -o exa $(objs)

main.o : main.c
	@cc -c -o main.o main.c

grid.o : grid.c
	@cc -c -o grid.o grid.c

fexdet.o : fexdet.c
	@cc -c -o fexdet.o fexdet.c

syscall.o : syscall.c
	@cc -c -o syscall.o syscall.c

list.o : lib/list.c
	@cc -c -o list.o lib/list.c

.PHONY : clean

clean : 
	-rm exa $(objs)