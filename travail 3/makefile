
NOM=TP3

CC=g++

OBJ=$(NOM).o\
	Arc.o\
    AttributNonDefinieXML.o\
    DocumentXML.o\
    ElementXML.o\
    Graphe.o\
    Lecteur.o\
    NoeudXML.o\
    TexteXML.o

.cpp.o :
	$(CC) $(FLAGS) -c $<

$(NOM) : $(OBJ)
	$(CC) -o $(NOM) $(OBJ)

Arc.cpp : Arc.hpp

AttributNonDefinieXML.cpp : AttributNonDefinieXML.hpp

DocumentXML.cpp : DocumentXML.hpp ElementXML.hpp

ElementXML.cpp : ElementXML.hpp AttributNonDefinieXML.hpp NoeudXML.hpp

Lecteur.cpp : Lecteur.hpp DocumentXML.hpp ElementXML.hpp

Graphe.cpp : Graphe.hpp Arc.hpp

NoeudXML.cpp : NoeudXML.hpp

TexteXML.cpp : TexteXML.hpp NoeudXML.hpp

$(NOM).cpp : Lecteur.hpp Graphe.hpp ElementXML.hpp DocumentXML.hpp

clean :
	\rm -f *.o
	\rm -f $(NOM)

archive : clean
	\rm -f $(NOM).tar
	\rm -f $(NOM).tar.gz
	tar cvf $(NOM).tar *
	gzip $(NOM).tar
