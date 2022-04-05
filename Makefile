proceed:
	g++ -Wall -Werror -std=c++2a -g *.cpp -o sweep
	./sweep input.txt

compile:
	g++ -Wall -Werror -std=c++2a -g *.cpp -o sweep

run:
	./sweep input.txt
