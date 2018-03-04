cache : main.o functions.o
	g++ -g -o cache main.o functions.o

main.o : main.cpp header.h
	g++ -g -c -Wall main.cpp

functions.o: functions.cpp header.h
	g++ -g -c -Wall functions.cpp

clean:
	rm cache main.o functions.o 

