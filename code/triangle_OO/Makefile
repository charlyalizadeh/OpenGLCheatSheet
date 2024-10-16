NAME=triangle_OO
SRCS=$(wildcard src/*.cpp)
OBJS=$(subst src,obj,$(subst .cpp,.o,$(SRCS)))
INCLUDES=include include/glad
FLAGS= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
CC=g++

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o bin/$(NAME) $(FLAGS)

$(OBJS): obj/%.o: src/%.cpp
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	rm -f bin/$(NAME)

fclean: clean
	rm -f obj/*

re: fclean $(NAME)

build:
	mkdir -p ./bin
	mkdir -p ./obj
