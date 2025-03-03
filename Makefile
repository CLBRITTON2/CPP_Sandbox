all: main

main: 
	g++ -std=c++20 -g -O0 ./src/*.cpp -I./src -o main

clean:
	rm -f main

.PHONY: clean all