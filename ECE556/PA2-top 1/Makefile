# Compiler to use
CXX = g++

# Compiler flags
# -Wall for compiler warnings, -g for debugging information
CXXFLAGS = -O3 -std=c++17

# Target executable name
TARGET = fp

# Object files
OBJS = main.o

# Rule to link the program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile the source files
main.o: main.cpp fp.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Rule for cleaning up
clean:
	rm -f $(TARGET) $(OBJS) *.rpt

# Phony targets
.PHONY: clean
