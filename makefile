CFLAGS = g++ -c -Ofast -std=c++11 -g
LFLAGS = g++ -Ofast -std=c++11 -o a
OBJS = main.o

out: $(OBJS)
	$(LFLAGS) $(CFLAGS)

main.o : Main.cpp
	$(CFLAGS) Main.cpp

Main.cpp : Header.h

clean:
	rm *.o
	rm *.exe

run: out
	.\a.exe