
all: run

run: build 
	./main
	make clean

build:
	g++ -std=c++17 -o main *.cc -fsanitize=address

clean:
	rm -rfv main