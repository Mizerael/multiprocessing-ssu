all: single multi

multi: parallel/src/src.cpp utils/test.cpp parallel/main.cpp
	g++ -fopenmp $^ -o $@

single: serrial/src/src.cpp utils/test.cpp serrial/main.cpp
	g++ $^ -o $@

clean:
	rm -f multi single