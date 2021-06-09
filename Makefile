objs = main.o grid.o fexdet.o syscall.o

exa : $(objs)
	@gcc -o exa $(objs)

main.o : main.c
	@gcc -c -o main.o main.c

grid.o : grid.c
	@gcc -c -o grid.o grid.c

fexdet.o : fexdet.c
	@gcc -c -o fexdet.o fexdet.c

syscall.o : syscall.c
	@gcc -c -o syscall.o syscall.c

.PHONY : clean

clean : 
	-rm exa $(objs)