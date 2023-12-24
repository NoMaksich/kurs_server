CC = g++
CFLAGS = -g -O0 -Wall
LIBS = -lcryptopp

SRCS = main.cpp Server.cpp ErrorLog.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = server

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC)
