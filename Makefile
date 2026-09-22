# Makefile
#
# make       -> build engine
# make test  -> build and run tests
# make clean -> remove build folder

CXX = g++
CXXFLAGS = -std=c++17 -Wall

ENGINE_SRC = engine/src/mmain.cpp
ENGINE_OUT = engine/build/math_engine

TEST_SRC = engine/tests/test_parser.cpp
TEST_OUT = engine/build/test_parser

.PHONY: all test clean

all: $(ENGINE_OUT)

$(ENGINE_OUT): $(ENGINE_SRC) engine/include/parser.h
	mkdir -p engine/build
	$(CXX) $(CXXFLAGS) -o $(ENGINE_OUT) $(ENGINE_SRC)
	codesign --force --sign - $(ENGINE_OUT) 2>/dev/null || true

test: $(TEST_OUT)
	./$(TEST_OUT)

$(TEST_OUT): $(TEST_SRC) engine/include/parser.h
	mkdir -p engine/build
	$(CXX) $(CXXFLAGS) -o $(TEST_OUT) $(TEST_SRC)
	codesign --force --sign - $(TEST_OUT) 2>/dev/null || true

clean:
	rm -rf engine/build