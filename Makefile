all: main

main: main.o funcoesgerais.o cliente.o funcionario.o principal.o
	gcc -o main main.o funcoesgerais.o cliente.o funcionario.o principal.o -lpanel -lncurses

main.o: main.c funcoesgerais.h cliente.h funcionario.h principal.h  
	gcc -o main.o main.c -lpanel -lncurses -c

funcoesgerais.o: funcoesgerais.c funcoesgerais.h
	gcc -o funcoesgerais.o funcoesgerais.c -lpanel -lncurses -c

cliente.o: cliente.c cliente.h
	gcc -o cliente.o cliente.c -lpanel -lncurses -c

funcionario.o: funcionario.c funcionario.h
	gcc -o funcionario.o funcionario.c -lpanel -lncurses -c 

principal.o: principal.c principal.h
	gcc -o principal.o principal.c -lpanel -lncurses -c

clear:
	rm *.o

super: 
	make all && ./main && make clear


