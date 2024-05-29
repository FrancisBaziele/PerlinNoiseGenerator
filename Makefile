CPLUS_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

app: build

build: main.o  perlin.hpp
	@echo "Linking Object Files..."
	g++ main.o  -o build  $(CPLUS_FLAGS) && ./build

main.o : main.cpp
	g++ $(CPLUS_FLAGS) -c main.cpp

perlin.o : perlin.hpp
	g++ $(CPLUS_FLAGS) -c perlin.cpp

clean: 
	@echo "Rremoving everything but source files..."
	rm main.o perlin.o build