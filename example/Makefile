# remove asserts in release builds
# CXXFLAGS := -DNDEBUG
CXXFLAGS = $(shell cat compile_flags.txt)


CXX := g++

default: bot

bot: bot.cpp debug.hpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
# %: %.cpp
# $(CXX) $(CXXFLAGS) -c $< -o $@

clear:
	rm *.o
