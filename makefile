rez:main.o kohonenmap.o
	g++ main.o kohonenmap.o -o rez
main.o:main.cpp
	g++ -c -g main.cpp
field.o:kohonenmap.cpp kohonenmap.h
	g++ -c -g kohonenmap.cpp

.PHONY:clear
clean:
	rm rez main.o kohonenmap.o 
