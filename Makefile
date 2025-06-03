.PHONY: all test clean editor client common server build

compile-debug:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug $(EXTRA_GENERATE)
	cmake --build  build/ $(EXTRA_COMPILE)

run-tests: compile-debug

	./build/CS2D_tests

run-client:  
	cd "$(CURDIR)" && ./build/CS2D_client 127.0.0.1 7777

run-client2:  
	cd "$(CURDIR)" && ./build/CS2D_client 127.0.0.1 8080

run-client3:
	cd "$(CURDIR)" && ./build/CS2D_client 127.0.0.1 5048

valgrind-client:
	cd "$(CURDIR)" && valgrind ./build/CS2D_client 127.0.0.1 7777

valgrind-client2:
	cd "$(CURDIR)" && valgrind ./build/CS2D_client 127.0.0.1 8080

valgrind-client3:
	cd "$(CURDIR)" && valgrind ./build/CS2D_client 127.0.0.1 5048

run-server: 

	./build/CS2D_server 7777

valgrind-server:
	valgrind --leak-check=full --show-leak-kinds=all ./build/CS2D_server 7777


valgrind-debug: compile-debug
	valgrind --leak-check=full --show-leak-kinds=all ./build/CS2D_tests

all: clean valgrind-debug

clean:
	rm -Rf build/

run-client-gdb:  
	cd "$(CURDIR)" && gdb ./build/CS2D_client 127.0.0.1 7777

run-server-gdb: 

	gdb ./build/CS2D_server 7777
