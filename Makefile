all: UDmain.o Dmain.o floodfill_g.o floodfill_m.o
	g++ -w -o ud.out UDmain.o -Wno-deprecated
	g++ -w -o d.out Dmain.o -Wno-deprecated
	g++ -w -o ffg.out floodfill_g.o -Wno-deprecated
	g++ -w -o ffm.out floodfill_m.o -Wno-deprecated 

Dmain.o: Dmain.cpp
	g++ -c Dmain.cpp -Wno-deprecated

UDmain.o: UDmain.cpp
	g++ -c UDmain.cpp -Wno-deprecated

floodfill_g.o: floodfill_g.cpp
	g++ -c floodfill_g.cpp -Wno-deprecated

floodfill_m.o: floodfill_m.cpp
	g++ -c floodfill_m.cpp -Wno-deprecated

clean:
	rm -f *.o 
	rm -f *.out
