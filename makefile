CC=g++ -std=c++11

all: utrip.out

utrip.out: main.o BookedItem.o BookingManager.o Filter.o Hotel.o HotelsDataManager.o User.o
		${CC} main.o BookedItem.o BookingManager.o Filter.o Hotel.o HotelsDataManager.o User.o -o utrip.out


main.o: main.cpp HotelsDataManager.hpp
		${CC} -c main.cpp

Filter.o: Filter.cpp Filter.hpp Hotel.hpp 
		${CC} -c Filter.cpp

HotelsDataManager.o: HotelsDataManager.cpp HotelsDataManager.hpp defines.hpp Hotel.hpp User.hpp Filter.hpp
		${CC} -c HotelsDataManager.cpp

Hotel.o: Hotel.cpp Hotel.hpp BookingManager.hpp
		${CC} -c Hotel.cpp

User.o: User.cpp User.hpp BookingManager.hpp
		${CC} -c User.cpp

BookingManager.o: BookingManager.cpp BookingManager.hpp BookedItem.hpp
		${CC} -c BookingManager.cpp

BookedItem.o: BookedItem.cpp BookedItem.hpp
		${CC} -c BookedItem.cpp



.PHONY:
clean:
	rm *.o
	rm utrip.out