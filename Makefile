all: Main

Main: Main.o XTR.o GFP2.o GFP.o BigNumber.o
	g++ -o Main Main.o XTR.o GFP2.o GFP.o BigNumber.o

Main.o: main.cpp
	g++ -c main.cpp

XTR.o: XTR.cpp XTR.hpp
	g++ -c XTR.cpp

GFP2.o: GFP2.cpp GFP2.hpp
	g++ -c GFP2.cpp

GFP.o: GFP.cpp GFP.hpp
	g++ -c GFP.cpp

BigNumber.o: BigNumber.cpp BigNumber.hpp
	g++ -c BigNumber.cpp

clean:
	rm -f *.o Main
