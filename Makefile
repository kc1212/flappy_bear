default: 
	g++ main.cpp -lsdl2 -framework Cocoa -o output

clean: 
	rm output

run: 
	./output	