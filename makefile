CC := g++ -std=c++11 -pedantic
BUILD_DIR=build

all: $(BUILD_DIR) a.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

a.out : $(BUILD_DIR)/main.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/request.o $(BUILD_DIR)/response.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/ExceptionHandler.o $(BUILD_DIR)/ProcessHandler.o $(BUILD_DIR)/UsersRepository.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/System.o $(BUILD_DIR)/Movie.o $(BUILD_DIR)/MovieRepository.o $(BUILD_DIR)/Reply.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/sha256.o $(BUILD_DIR)/AI.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/RequestHandlers.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/request.o $(BUILD_DIR)/response.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/ExceptionHandler.o $(BUILD_DIR)/ProcessHandler.o $(BUILD_DIR)/UsersRepository.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/System.o $(BUILD_DIR)/Movie.o $(BUILD_DIR)/MovieRepository.o $(BUILD_DIR)/Reply.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/sha256.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/AI.o $(BUILD_DIR)/RequestHandlers.o -o a.out

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/my_server.o: Myfiles/my_server.cpp Myfiles/my_server.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c Myfiles/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o : Myfiles/main.cpp Myfiles/Comment.h Myfiles/Reply.h Myfiles/ExceptionHandler.h Myfiles/Movie.h Myfiles/MovieRepository.h Myfiles/Publisher.h Myfiles/System.h Myfiles/User.h Myfiles/UsersRepository.h Myfiles/ProcessHandler.h Myfiles/my_server.hpp
	$(CC) -c Myfiles/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Comment.o : Myfiles/Comment.cpp Myfiles/Comment.h
	$(CC) -c Myfiles/Comment.cpp -o $(BUILD_DIR)/Comment.o

$(BUILD_DIR)/Reply.o : Myfiles/ExceptionHandler.h Myfiles/Reply.h Myfiles/Reply.cpp
	$(CC) -c Myfiles/Reply.cpp -o $(BUILD_DIR)/Reply.o

$(BUILD_DIR)/ExceptionHandler.o : Myfiles/ExceptionHandler.cpp Myfiles/ExceptionHandler.h
	$(CC) -c Myfiles/ExceptionHandler.cpp -o $(BUILD_DIR)/ExceptionHandler.o

$(BUILD_DIR)/ProcessHandler.o: Myfiles/ProcessHandler.h Myfiles/ProcessHandler.cpp Myfiles/ExceptionHandler.h Myfiles/UsersRepository.h Myfiles/User.h Myfiles/Publisher.h Myfiles/MovieRepository.h Myfiles/sha256.h Myfiles/AI.h Myfiles/my_server.hpp
	$(CC) -c Myfiles/ProcessHandler.cpp -o $(BUILD_DIR)/ProcessHandler.o

$(BUILD_DIR)/Movie.o : Myfiles/Movie.h Myfiles/Movie.cpp Myfiles/Comment.h Myfiles/Reply.h Myfiles/ExceptionHandler.h
	$(CC) -c Myfiles/Movie.cpp -o $(BUILD_DIR)/Movie.o

$(BUILD_DIR)/MovieRepository.o : Myfiles/MovieRepository.cpp Myfiles/MovieRepository.h Myfiles/Movie.h Myfiles/ExceptionHandler.h
	$(CC) -c Myfiles/MovieRepository.cpp -o $(BUILD_DIR)/MovieRepository.o

$(BUILD_DIR)/Publisher.o : Myfiles/Publisher.h Myfiles/Publisher.cpp Myfiles/User.h Myfiles/Movie.h Myfiles/MovieRepository.h Myfiles/ExceptionHandler.h
	$(CC) -c Myfiles/Publisher.cpp -o $(BUILD_DIR)/Publisher.o

$(BUILD_DIR)/System.o: Myfiles/UsersRepository.h Myfiles/MovieRepository.h Myfiles/ProcessHandler.h Myfiles/System.h Myfiles/System.cpp Myfiles/my_server.hpp Myfiles/RequestHandlers.h
	$(CC) -c Myfiles/System.cpp -o $(BUILD_DIR)/System.o

$(BUILD_DIR)/User.o : Myfiles/User.h Myfiles/User.cpp Myfiles/ExceptionHandler.h Myfiles/Movie.h Myfiles/MovieRepository.h Myfiles/AI.h
	$(CC) -c Myfiles/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/UsersRepository.o : Myfiles/User.h Myfiles/ExceptionHandler.h Myfiles/UsersRepository.h Myfiles/UsersRepository.cpp
	$(CC) -c Myfiles/UsersRepository.cpp -o $(BUILD_DIR)/UsersRepository.o

$(BUILD_DIR)/sha256.o: Myfiles/sha256.h Myfiles/sha256.cpp
	$(CC) -c Myfiles/sha256.cpp -o $(BUILD_DIR)/sha256.o

$(BUILD_DIR)/AI.o: Myfiles/AI.h Myfiles/AI.cpp Myfiles/Movie.h Myfiles/UsersRepository.h Myfiles/MovieRepository.h Myfiles/User.h
	$(CC) -c Myfiles/AI.cpp -o $(BUILD_DIR)/AI.o

$(BUILD_DIR)/RequestHandlers.o : Myfiles/RequestHandlers.cpp Myfiles/RequestHandlers.h Myfiles/ProcessHandler.h Myfiles/ExceptionHandler.h server/server.hpp
	$(CC) -c Myfiles/RequestHandlers.cpp -o $(BUILD_DIR)/RequestHandlers.o

.PHONY : clean
clean:
	rm -r $(BUILD_DIR) *.o *.out  &> /dev/null