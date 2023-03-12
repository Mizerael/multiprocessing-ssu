all: single multi

multi: src/src.cpp main.cpp
	g++ -fopenmp $^ -o $@

single: src/src.cpp main.cpp
	g++ $^ -o $@

clean:
	rm -f multi single