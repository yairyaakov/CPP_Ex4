#207723198
# yair852258@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Default target
all: main test

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o $(LDFLAGS)

test: Test.o
	$(CXX) $(CXXFLAGS) -o test Test.o $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) -c Test.cpp

# Specific targets to run executables
tree: main
	./main

runtest: test
	./test

valgrind: main test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test

# Clean target
clean:
	rm -f main test *.o