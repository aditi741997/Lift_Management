CFLAGS = -c -Ofast -std=c++11 -g
LFLAGS = -Ofast -std=c++11 -o
OBJS =  state.o

out: $(OBJS) main.o
	g++ $(LFLAGS) $(OBJS) main.o -o out

main.o : Main.cpp Header.h
	g++ $(CFLAGS) Main.cpp

state.o : State.cpp Header.h
	g++ $(CFLAGS) State.cpp

clean:
	rm *.o
	rm *.exe

run: out
	.\a.exe