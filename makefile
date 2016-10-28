CFLAGS = -c -Ofast -std=c++11 -g
LFLAGS = -Ofast -std=c++11 -o
OBJS =  state.o action.o

out: $(OBJS) main.o
	g++ $(LFLAGS) $(OBJS) main.o -o out

state.o : State.cpp Header.h
	g++ $(CFLAGS) State.cpp

action.o : Action.cpp Header.h
	g++ $(CFLAGS) Action.cpp

main.o : Main.cpp Header.h
	g++ $(CFLAGS) Main.cpp

clean:
	rm *.o
	rm *.exe

run: out
	.\a.exe