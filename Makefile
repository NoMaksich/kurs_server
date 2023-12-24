CC = g++
CFLAGS = -g -O0 -Wall
LIBS = -lcryptopp
LDFLAGS = -lUnitTest++ -lcryptopp

SRCS_SERVER = main.cpp Server.cpp ErrorLog.cpp
OBJS_SERVER = $(SRCS_SERVER:.cpp=.o)
EXEC_SERVER = server

SRCS_TEST = test.cpp Server.cpp ErrorLog.cpp
OBJS_TEST = $(SRCS_TEST:.cpp=.o)
EXEC_TEST = test

all: $(EXEC_SERVER) $(EXEC_TEST)

$(EXEC_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBS) -o $(EXEC_SERVER)

$(EXEC_TEST): $(OBJS_TEST)
	$(CC) $(CFLAGS) $(OBJS_TEST) $(LDFLAGS) -o $(EXEC_TEST)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_TEST) $(EXEC_SERVER) $(EXEC_TEST)

run_server: $(EXEC_SERVER)
	./$(EXEC_SERVER)

run_test: $(EXEC_TEST)
	./$(EXEC_TEST)
