all:
	gcc -O0 -flto c_src.c -o c_prog
	g++ -O0 -flto cpp_src.cpp -o cpp_prog

test:
	./test.sh

clean:
	@rm c_prog cpp_prog output.txt input.txt
