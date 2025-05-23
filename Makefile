.PHONY: all test clean editor client common server build

compile-debug:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug $(EXTRA_GENERATE)
	cmake --build  build/ $(EXTRA_COMPILE)

run-tests: compile-debug

	./build/CS2D_tests

run-client:  compile-debug
	cd "$(CURDIR)" && ./build/CS2D_client

run-server: compile-debug

	./build/CS2D_server

valgrind-debug: compile-debug
	valgrind ./build/CS2D_tests

all: clean valgrind-debug

clean:
	rm -Rf build/