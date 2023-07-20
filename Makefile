all:
	g++ -I include -l SDL2 -o attempt main.cpp
	chmod +x attempt
	./attempt
	