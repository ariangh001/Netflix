CC := g++ -std=c++11

all : a.out

a.out : main.o  ExceptionHandler.o InputHandler.o 
	$(CC) main.o  ExceptionHandler.o InputHandler.o 

main.o : main.cpp Comment.h CommentRepository.h ExceptionHandler.h InputHandler.h Movie.h MovieRepository.h Publisher.h System.h User.h UsersRepository.h
	$(CC) -c main.cpp -o main.o

Comment.o :

CommentRepository.o :

ExceptionHandler.o : ExceptionHandler.cpp ExceptionHandler.h
	$(CC) -c ExceptionHandler.cpp -o ExceptionHandler.o
InputHandler.o : InputHandler.h InputHandler.cpp ExceptionHandler.h
	$(CC) -c InputHandler.cpp -o InputHandler.o
Movie.o :

MovieRepository.o : 

Publisher.o : 

System.o: 

User.o :

UsersRepository.o :


.PHONY : clean
clean:
	rm -r *.o