all: mpi_multi

mpi_multi: source/source.cpp main.cpp
	mpic++ $^ -o $@

clean:
	rm -f mpi_multi
