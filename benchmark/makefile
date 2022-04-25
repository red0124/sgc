FLAGS=-O3 -flto -Wall -Wextra

gcc:
	gcc sgc.c benchmark_common.c ${FLAGS} -o sgc
	g++ std.cpp benchmark_common.c ${FLAGS} -o std

clang:
	clang-13 sgc.c benchmark_common.c ${FLAGS} -o sgc
	clang++-13 std.cpp benchmark_common.c ${FLAGS} -o std

clang14:
	clang sgc.c benchmark_common.c ${FLAGS} -o sgc
	clang++ std.cpp benchmark_common.c ${FLAGS} -o std

clean:
	rm sgc std

run:
	./benchmark.sh | ./pretty_output.py
