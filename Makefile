SRCS    = $(shell /bin/ls *.cc)
CFLAGS   = -DOP_ASSIGN

.SUFFIXES: $(SUFFIXES) .cpp

%.o: %.cpp
#	g++ -c $(CFLAGS) $<
	g++ -c $(CFLAGS) -fno-elide-constructors $<

OBJS = main.o parse.o eval.o Cell.o flat_list_eval.o SymbolTableStack.o list_utility.o

main: $(OBJS)
	g++ -g $(CFLAGS) -o $@ $(OBJS) -lm

main.o: Cell.hpp cons.hpp parse.hpp eval.hpp main.cpp
	g++ -c -g main.cpp

parse.o: Cell.hpp cons.hpp parse.hpp parse.cpp
	g++ -c -g parse.cpp

eval.o: Cell.hpp cons.hpp SymbolTableStack.hpp flat_list_eval.hpp list_utility.hpp eval.hpp eval.cpp 
	g++ -c -g eval.cpp

Cell.o: Cell.hpp Cell.cpp
	g++ -c -g Cell.cpp

flat_list_eval.o: cons.hpp flat_list_eval.hpp flat_list_eval.cpp
	g++ -c -g flat_list_eval.cpp

SymbolTable.o: cons.hpp SymbolTableStack.hpp SymbolTableStack.cpp
	g++ -c -g SymbolTableStack.cpp

list_utility.o: cons.hpp list_utility.hpp list_utility.cpp
	g++ -c -g list_utility.cpp

doc:
	doxygen doxygen.config

test:
	rm -f testoutput.txt
	./main testinput.txt > testoutput.txt
	diff testreference.txt testoutput.txt

clean:
	rm -f core *~ $(OBJS) main main.exe testoutput.txt
