CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
SRCDIR = src
INCLUDEDIR = include
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/Firewall.cpp $(SRCDIR)/WebServer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = load_balancer

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

