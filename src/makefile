CFLAGS = -c -Ofast -std=c++11 -g
LFLAGS = -Ofast -std=c++11
OBJS =  Agent.o

out: $(OBJS) Main.o
	g++ -o out $(OBJS) Main.o $(LFLAGS)

Agent.o : Agent.cpp Agent.h
	g++ Agent.cpp $(CFLAGS)

Main.o : Main.cpp Agent.h
	g++ Main.cpp $(CFLAGS)

clean:
	rm *.o
	rm out

run: out
