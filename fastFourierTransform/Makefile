all: single multi

multi: src/src.cpp src/config.cpp main.cpp
	g++ -fopenmp $^ -o $@

single: src/src.cpp src/config.cpp main.cpp
	g++ $^ -o $@

clean:
	rm -f multi single