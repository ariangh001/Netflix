CC := g++ -std=c++11

all : a.out

a.out : main.o  ExceptionHandler.o InputHandler.o ProcessHandler.o UsersRepository.o User.o Publisher.o System.o Movie.o MovieRepository.o
	$(CC) main.o  ExceptionHandler.o InputHandler.o ProcessHandler.o UsersRepository.o User.o Publisher.o System.o Movie.o MovieRepository.o

main.o : main.cpp Comment.h CommentRepository.h ExceptionHandler.h InputHandler.h Movie.h MovieRepository.h Publisher.h System.h User.h UsersRepository.h
	$(CC) -c main.cpp -o main.o

#Comment.o :

#CommentRepository.o :

ExceptionHandler.o : ExceptionHandler.cpp ExceptionHandler.h
	$(CC) -c ExceptionHandler.cpp -o ExceptionHandler.o

InputHandler.o : InputHandler.h InputHandler.cpp ExceptionHandler.h ProcessHandler.h
	$(CC) -c InputHandler.cpp -o InputHandler.o

ProcessHandler.o: ProcessHandler.h ProcessHandler.cpp ExceptionHandler.h UsersRepository.h User.h Publisher.h
	$(CC) -c ProcessHandler.cpp -o ProcessHandler.o

Movie.o :

#MovieRepository.o :

Publisher.o : Publisher.h Publisher.cpp User.h Movie.h MovieRepository.h
	$(CC) -c Publisher.cpp -o Publisher.o

System.o: UsersRepository.h MovieRepository.h CommentRepository.h User.h Movie.h Comment.h InputHandler.h ProcessHandler.h System.h System.cpp
	$(CC) -c System.cpp -o System.o

#User.o :

UsersRepository.o : User.h ExceptionHandler.h UsersRepository.h UsersRepository.cpp
	$(CC) -c UsersRepository.cpp -o UsersRepository.o


.PHONY : clean
clean:
	rm -r *.o