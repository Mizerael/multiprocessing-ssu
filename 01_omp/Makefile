.PHONY: all

all: single multi

multi: main.cpp
	g++ -fopenmp $^ -o $@

single: main.cpp
	g++ $^ -o $@

clean:
	rm -f multi single