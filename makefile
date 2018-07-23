CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g -Wall $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)
WALL=-Wall

ifndef INSTANCE
all: clean main default
else
all: clean main instance
endif

SRCS=main.cpp
OBJS=$(subst .cc,.o,$(SRCS))
main: $(OBJS)
	$(CXX) $(WALL) $(SRCS) -o main
instance:
	./main instancesTxt/$(INSTANCE)
clean:
	$(RM) main
default:
	./main instancesTxt/5nodes_Instance1.txt
distclean: clean $(RM) main
