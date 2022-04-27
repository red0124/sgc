FLAGS=-O3 -flto -Wall -Wextra

gcc:
	gcc sgc.c common.c ${FLAGS} -o sgc
	g++ std.cpp common.c ${FLAGS} -o std

clang:
	clang sgc.c common.c ${FLAGS} -o sgc
	clang++ std.cpp common.c ${FLAGS} -o std

clang13:
	clang-13 sgc.c common.c ${FLAGS} -o sgc
	clang++-13 std.cpp common.c ${FLAGS} -o std

clean:
	rm sgc std
