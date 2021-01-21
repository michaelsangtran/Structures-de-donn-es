NOM=tp1

CC= g++ -std=c++11

OBJ=$(NOM).o 

.cpp.o :
	$(CC) -c $<

$(NOM) : $(OBJ)
	$(CC) -o $(NOM) $(OBJ)

$(NOM).cpp : Constantes.hpp

.PHONY: clean

clean :
	\rm -f *.o
	\rm -f $(NOM)