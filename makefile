CFLAGS = -c -Ofast -std=c++11 -g
LFLAGS = -Ofast -std=c++11
OBJS =  State.o Action.o

out: $(OBJS) Main.o
	g++ -o out $(OBJS) Main.o $(LFLAGS)

State.o : State.cpp Header.h
	g++ State.cpp $(CFLAGS)

Action.o : Action.cpp Header.h
	g++ Action.cpp $(CFLAGS)

Main.o : Main.cpp Header.h
	g++ Main.cpp $(CFLAGS)
 
clean:
	rm *.o
	rm out

run: out
	.\a.exe