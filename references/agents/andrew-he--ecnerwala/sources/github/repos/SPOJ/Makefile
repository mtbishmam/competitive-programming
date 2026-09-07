CXX = g++
CXXFLAGS = -O2 -Wall -Wextra

TARGET := $(notdir $(CURDIR))

TESTS := $(sort $(patsubst %.in,%,$(wildcard *.in)))

all: $(TARGET)

clean:
	-rm -rf $(TARGET) *.res

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(TARGET)
	time ./$(TARGET)

%.res: $(TARGET) %.in
	time ./$(TARGET) < $*.in > $*.res

test%: %.res
	diff $*.res $*.out

test: $(patsubst %,test%,$(TESTS))

.PHONY: all clean run test

.PRECIOUS: $(patsubst %,%.res,$(TESTS))
