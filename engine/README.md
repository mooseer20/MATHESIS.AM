
# Makefile
#
# Ինչո՞ւ ենք սա ավելացնում. որ build հրամանը մեկ տեղում լինի, ոչ թե
# ամեն անգամ ձեռքով մուտքագրված terminal-ում (որտեղ սխալվելը հեշտ է):
#
# Օգտագործում.
#   make          -> build անել engine-ը
#   make clean    -> ջնջել build/ folder-ը
 
CXX = g++
CXXFLAGS = -std=c++17 -Wall
 
ENGINE_SRC = engine/src/main.cpp
ENGINE_OUT = engine/build/math_engine
 
.PHONY: all clean
 
all: $(ENGINE_OUT)
 
$(ENGINE_OUT): $(ENGINE_SRC)
	mkdir -p engine/build
	$(CXX) $(CXXFLAGS) -o $(ENGINE_OUT) $(ENGINE_SRC)
 
clean:
	rm -rf engine/build
 