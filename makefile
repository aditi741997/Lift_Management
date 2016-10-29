CFLAGS = -c -Ofast -std=c++11 -g
LFLAGS = -Ofast -std=c++11 -o
OBJS =  State.o Action.o

out: $(OBJS) Main.o
	g++ $(LFLAGS) $(OBJS) Main.o -o out

State.o : State.cpp Header.h
	g++ $(CFLAGS) State.cpp

Action.o : Action.cpp Header.h
	g++ $(CFLAGS) Action.cpp

Main.o : Main.cpp Header.h
	g++ $(CFLAGS) Main.cpp

clean:
	rm *.o
	rm *.exe

run: out
	.\a.exe