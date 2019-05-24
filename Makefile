CC := g++ -std=c++11

all : a.out

a.out : main.o  ExceptionHandler.o InputHandler.o ProcessHandler.o UsersRepository.o User.o Publisher.o System.o Movie.o MovieRepository.o Reply.o Comment.o sha256.o AI.o
	$(CC) main.o  ExceptionHandler.o InputHandler.o ProcessHandler.o UsersRepository.o User.o Publisher.o System.o Movie.o MovieRepository.o Reply.o Comment.o sha256.o AI.o

main.o : main.cpp Comment.h Reply.h ExceptionHandler.h InputHandler.h Movie.h MovieRepository.h Publisher.h System.h User.h UsersRepository.h ProcessHandler.h
	$(CC) -c main.cpp -o main.o

Comment.o : Comment.cpp Comment.h
	$(CC) -c Comment.cpp -o Comment.o

Reply.o : ExceptionHandler.h Reply.h Reply.cpp
	$(CC) -c Reply.cpp -o Reply.o

ExceptionHandler.o : ExceptionHandler.cpp ExceptionHandler.h
	$(CC) -c ExceptionHandler.cpp -o ExceptionHandler.o

InputHandler.o : InputHandler.h InputHandler.cpp ExceptionHandler.h ProcessHandler.h User.h
	$(CC) -c InputHandler.cpp -o InputHandler.o

ProcessHandler.o: ProcessHandler.h ProcessHandler.cpp ExceptionHandler.h UsersRepository.h User.h Publisher.h MovieRepository.h sha256.h
	$(CC) -c ProcessHandler.cpp -o ProcessHandler.o

Movie.o : Movie.h Movie.cpp Comment.h Reply.h ExceptionHandler.h
	$(CC) -c Movie.cpp -o Movie.o

MovieRepository.o : MovieRepository.cpp MovieRepository.h Movie.h ExceptionHandler.h
	$(CC) -c MovieRepository.cpp -o MovieRepository.o

Publisher.o : Publisher.h Publisher.cpp User.h Movie.h MovieRepository.h ExceptionHandler.h
	$(CC) -c Publisher.cpp -o Publisher.o

System.o: UsersRepository.h MovieRepository.h InputHandler.h ProcessHandler.h System.h System.cpp
	$(CC) -c System.cpp -o System.o

User.o : User.h User.cpp ExceptionHandler.h Movie.h MovieRepository.h AI.h
	$(CC) -c User.cpp -o User.o

UsersRepository.o : User.h ExceptionHandler.h UsersRepository.h UsersRepository.cpp
	$(CC) -c UsersRepository.cpp -o UsersRepository.o

sha256.o: sha256.h sha256.cpp
	$(CC) -c sha256.cpp -o sha256.o

AI.o: AI.h AI.cpp Movie.h
	$(CC) -c AI.cpp -o AI.o

.PHONY : clean
clean:
	rm -r *.o