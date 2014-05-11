main: main.o chaitin.o stack.o graph.o
	gcc main.o chaitin.o stack.o graph.o -o cgc
test: chaitin.o stack.o graph.o test.o
	gcc test.o chaitin.o stack.o graph.o -o tests.out
main.o: main.c chaitin.h
	gcc -c main.c
test.o: test.c chaitin.h stack.h graph.h
	gcc -c test.c
chaitin.o: chaitin.c chaitin.h stack.h graph.h
	gcc -c chaitin.c
stack.o: stack.c stack.h graph.h
	gcc -c stack.c
graph.o: graph.c graph.h
	gcc -c graph.c

clean:
	rm -f *.o tests.out

