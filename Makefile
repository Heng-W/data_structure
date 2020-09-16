
CXX=g++
CXXFLAGS=-std=c++11 -Wall -O2

TARGET_DIR:=build
SRCS:=$(wildcard *.cpp)
TARGETS:=$(patsubst %.cpp,$(TARGET_DIR)/%,$(SRCS))


.PHONY: all clean

all: $(TARGET_DIR) $(TARGETS)

$(TARGET_DIR):
	mkdir -p $@

$(TARGET_DIR)/%: %.cpp
	@echo compile $^
	$(CXX) $(CXXFLAGS) $^ -o $@ 
	@echo

clean:
	rm -rf build/
