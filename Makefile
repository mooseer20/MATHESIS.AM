# Makefile
#
# make       -> build engine
# make test  -> build and run tests
# make clean -> remove build folder
# make demo  -> build derivative demo
# make sanitize -> for local testing
 #make variables -> for vars test
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow


sanitize:
	$(CXX) $(CXXFLAGS) -fsanitize=address,undefined -g \
	    -o engine/build/test_parser engine/tests/test_parser.cpp
	./engine/build/test_parser

ENGINE_SRC = engine/src/mmain.cpp
ENGINE_OUT = engine/build/math_engine

DEMO_SRC = engine/src/derivative_demo.cpp
DEMO_OUT = engine/build/derivative_demo

VARIABLE_DEMO_SRC = engine/src/variable_demo.cpp
VARIABLE_DEMO_OUT = engine/build/variable_demo



TEST_SRC = engine/tests/test_parser.cpp
TEST_OUT = engine/build/test_parser

.PHONY: all test demo variables clean

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
demo: $(DEMO_OUT)

$(DEMO_OUT): $(DEMO_SRC) engine/include/parser.h
	mkdir -p engine/build
	$(CXX) $(CXXFLAGS) -o $(DEMO_OUT) $(DEMO_SRC)


variables: $(VARIABLE_DEMO_OUT)
	./$(VARIABLE_DEMO_OUT)

$(VARIABLE_DEMO_OUT): $(VARIABLE_DEMO_SRC) engine/include/parser.h
	mkdir -p engine/build
	$(CXX) $(CXXFLAGS) -o $(VARIABLE_DEMO_OUT) $(VARIABLE_DEMO_SRC)


clean:
	rm -rf engine/build