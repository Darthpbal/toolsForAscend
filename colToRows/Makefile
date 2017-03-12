run:compile
	clear
	./program
	head clean*.txt
	tail clean*.txt

compile:clean
	g++ src/*.cpp -o program

clean:
	rm -f program clean*.txt
	clear
