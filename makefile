lab2: parser

parser: lexer.o frontend_lexer.o syntax.o tree.o frontend_syntax.o main.o
	g++ lexer.o frontend_lexer.o syntax.o tree.o frontend_syntax.o main.o -o parser

main.o: main.cpp
	g++ -c main.cpp

frontend_lexer.o: frontend_lexer.cpp
	g++ -c frontend_lexer.cpp

lexer.o: lexer.cpp
	g++ -c lexer.cpp

syntax.o: syntax.cpp
	g++ -c syntax.cpp

tree.o: tree.cpp
	g++ -c tree.cpp

frontend_syntax.o: frontend_syntax.cpp
	g++ -c frontend_syntax.cpp

clean:
	rm -rf *.o parser

run: lab2
	./parser
