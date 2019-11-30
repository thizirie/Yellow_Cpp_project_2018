CC = g++
CCFLAGS= -Wall -Werror -g 
SRC=  main.cc csvreader.cc Paint.cc Artist.cc Player.cc Sculpture.cc
LIB= -std=c++14  -lboost_thread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJ= $(SRC:.c=.o)
EXEC= main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC)  $^ -o $@  $(LIB)

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	rm -f $(EXEC)  
	rm -f *.o

