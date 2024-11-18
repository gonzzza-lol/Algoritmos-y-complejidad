output: main.o costos.o
	g++ main.o costos.o -o output

main.o: main.cpp
	g++ -c main.cpp

message.o: costos.cpp costos.h
	g++ -c costos.cpp

clean:
	rm *.o output