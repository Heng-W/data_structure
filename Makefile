
CXX=g++
CXXFLAGS=-std=c++11 -Wall -O2

TARGET_DIR:=build/linux
SRCS:=$(wildcard *.cpp)
TARGETS:=$(patsubst %.cpp,$(TARGET_DIR)/%,$(SRCS))


.PHONY: all

all: $(TARGET_DIR) $(TARGETS)

$(TARGET_DIR):
	mkdir -p $@

$(TARGET_DIR)/%: %.cpp
	@echo compile $^
	$(CXX) $(CXXFLAGS) $^ -o $@ 
	@echo

