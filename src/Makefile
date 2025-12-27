# remove asserts in release builds
# CXXFLAGS := -DNDEBUG
CXXFLAGS = $(shell cat compile_flags.txt)


CXX := g++

default: arena

arena: main.o process.o map.o
	$(CXX) $^ -o $@
	
%: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clear:
	rm *.o
