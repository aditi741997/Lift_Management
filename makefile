CFLAGS = -c -Ofast -std=c++11 -g
LFLAGS = -Ofast -std=c++11
OBJS =  State.o Action.o Sample.o Simulator.o

out: $(OBJS) Main.o
	g++ -o out $(OBJS) Main.o $(LFLAGS)

State.o : State.cpp Header.h
	g++ State.cpp $(CFLAGS)

Action.o : Action.cpp Header.h
	g++ Action.cpp $(CFLAGS)

Sample.o : Sample.cpp Sample.h
	g++ Sample.cpp $(CFLAGS)

Simulator.o : Simulator.cpp Simulator.h
	g++ Simulator.cpp $(CFLAGS)

Main.o : Main.cpp Sample.h Simulator.h
	g++ Main.cpp $(CFLAGS)
 
clean:
	rm *.o
	rm out

run: out
