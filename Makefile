all: memorydis.cpp
	g++ -o dis memorydis.cpp
clean:
	rm dis