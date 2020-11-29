all: Polinomio.o
	@echo Compilando
	@g++ main.cpp -o poly Polinomio.o
	@clear
	@./poly

valgrind: Polinomio.o
	@echo Compilando
	@g++ main.cpp -o poly Polinomio.o -g
	@clear
	@valgrind --leak-check=full --track-origins=yes ./poly

Polinomio.o: Polinomio.cpp Polinomio.h
	g++ -c Polinomio.cpp

