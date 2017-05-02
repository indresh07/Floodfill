all: UDmain.o Dmain.o floodfill_g.o floodfill_m.o
	g++ -w -o UD UDmain.o -Wno-deprecated
	g++ -w -o D Dmain.o -Wno-deprecated
	g++ -w -o floodfill_g floodfill_g.o -Wno-deprecated
	g++ -w -o floodfill_g.o floodfill_m.o -Wno-deprecated 

Dmain.o: Dmain.cpp
	g++ -c Dmain.cpp -Wno-deprecated

UDmain.o: UDmain.cpp
	g++ -c UDmain.cpp -Wno-deprecated

floodfill_g.o: floodfill_g.o.cpp
	g++ -c floodfill_g.o.cpp -Wno-deprecated

floodfill_m.o: floodfill_m.cpp
	g++ -c floodfill_m.cpp -Wno-deprecated

clean:
	rm -f *.o
