# Project: StockProfile

CPP      = g++
TARGET   = StockProfile
FLAGS   = -pedantic-errors -std=c++11

$(TARGET): Main.o StockProfile.o
	$(CPP) $(FLAGS) $^ -o $(TARGET)

Main.o: Main.cpp StockProfile.h
	$(CPP) $(FLAGS) -c Main.cpp -o Main.o 

StockProfile.o: StockProfile.cpp StockProfile.h
	$(CPP) $(FLAGS) -c StockProfile.cpp -o StockProfile.o 

clean: 
	rm -f StockProfile StockProfile.o Main.o

.PHONY: clean 

