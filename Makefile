CC = gcc
AR = ar
FLAGS = -Wall -g

make all: graph libgraph.so 

graph: main.o libgraph.so
	$(CC) $(FLAGS) -o graph main.o ./libgraph.so

priorityQ.o: priorityQ.h graph.h priorityQ.c
	$(CC) $(FLAGS) -c priorityQ.c

main.o: libgraph.so main.c
	$(CC) $(FLAGS) -c main.c

algo.o: algo.h graph.h priorityQ.h priorityQ.o algo.c
	$(CC) $(FLAGS) -c algo.c

libgraph.so: algo.o priorityQ.o
	$(CC) -shared -o libgraph.so algo.o priorityQ.o
	

.PHONY: clean all
clean: 
	rm -f *.o *.so libgraph.so graph