.PHONY: clean mrproper
CXX = g++
CXXFLAGS = -c -I include -Wextra -Wall -std=c++14
LDFLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system
EXEC = Snake

all: bin/$(EXEC)

bin/$(EXEC): bin/prog
	echo "#!/bin/bash\nexport LD_LIBRARY_PATH=lib\n./bin/prog" > bin/$(EXEC)
	chmod +x bin/$(EXEC)

bin/prog: bin/obj/main.o
	export LD_LIBRARY_PATH=lib
	$(CXX) bin/obj/main.o -o bin/prog $(LDFLAGS)

bin/obj/main.o: src/main.cpp
	$(CXX) src/main.cpp -o bin/obj/main.o $(CXXFLAGS)

clean:
	rm -rf bin/obj/*

mrproper: clean
	rm -f bin/$(EXEC) bin/prog
