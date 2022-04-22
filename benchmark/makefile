FLAGS=-O3 -flto -Wall -Wextra

all:
	gcc sgc.c benchmark_common.c ${FLAGS} -o sgc
	g++ std.cpp benchmark_common.c ${FLAGS} -o std

clean:
	rm sgc std

run:
	./benchmark.sh | ./pretty_output.py
