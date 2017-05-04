#  Author : Indresh Kumar Gupta
#  Purpose : To compile all the cpp files
#  Version : 1.1

all: obj/undirected_driver.o obj/directed_driver.o obj/floodfill_g.o obj/floodfill_m.o
	g++ -w -o bin/undirected_driver obj/undirected_driver.o -Wno-deprecated
	g++ -w -o bin/directed_driver obj/directed_driver.o -Wno-deprecated
	g++ -w -o bin/floodfill_g obj/floodfill_g.o -Wno-deprecated
	g++ -w -o bin/floodfill_m obj/floodfill_m.o -Wno-deprecated 

obj/directed_driver.o: src/directed_driver.cpp
	g++ -c -o obj/directed_driver.o src/directed_driver.cpp -Wno-deprecated

obj/undirected_driver.o: src/undirected_driver.cpp
	g++ -c -o  obj/undirected_driver.o src/undirected_driver.cpp -Wno-deprecated

obj/floodfill_g.o: src/floodfill_g.cpp
	g++ -c -o obj/floodfill_g.o src/floodfill_g.cpp -Wno-deprecated

obj/floodfill_m.o: src/floodfill_m.cpp
	g++ -c -o obj/floodfill_m.o src/floodfill_m.cpp -Wno-deprecated

clean:
	rm -f obj/*
	rm -f bin/*
