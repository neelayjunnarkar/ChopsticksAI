CC = g++-7.1
CFLAGS = -std=c++1z
TARGET = chopsticks_ai
OBJS = objs/main.o objs/Chopsticks.o objs/human.o objs/ai.o

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

objs/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o objs/main.o

objs/Chopsticks.o: src/Chopsticks.cpp
	$(CC) $(CFLAGS) -c src/Chopsticks.cpp -o objs/Chopsticks.o

objs/human.o: src/human.cpp
	$(CC) $(CFLAGS) -c src/human.cpp -o objs/human.o

objs/ai.o: src/ai.cpp
	$(CC) $(CFLAGS) -c src/ai.cpp -o objs/ai.o

run: all
	./$(TARGET)

clean:
	rm $(OBJS)
	rm $(TARGET)
