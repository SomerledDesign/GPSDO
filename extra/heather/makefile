###############################################################
#							      #
#  MAKEFILE for Linux					      #
#							      #
#							      #
###############################################################

all: heather

heather.o: heather.cpp heather.ch heathfnt.ch makefile
	g++ -c heather.cpp -Wno-write-strings

heathmsc.o: heathmsc.cpp heather.ch heathfnt.ch makefile
	g++ -c heathmsc.cpp -Wno-write-strings

heathui.o: heathui.cpp heather.ch heathfnt.ch makefile
	g++ -c heathui.cpp -Wno-write-strings

heathgps.o: heathgps.cpp heather.ch heathfnt.ch makefile
	g++ -c heathgps.cpp -Wno-write-strings

heather: heather.o heathmsc.o heathui.o heathgps.o
	g++ heather.o heathui.o heathgps.o heathmsc.o -o heather -lm -lX11

clean:
	rm heather.o heathui.o heathgps.o heathmsc.o heather


