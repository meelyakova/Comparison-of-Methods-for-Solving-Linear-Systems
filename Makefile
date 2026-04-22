CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall

TARGET = lab

SRCS = main.cpp matrix.cpp gauss.cpp lu.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)