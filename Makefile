main: main.cpp
	g++ main.cpp -o main

.PHONY: clean
clean:
	rm -f main

