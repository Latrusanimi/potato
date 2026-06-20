#ifndef SPIELER_H
#define SPIELER_H

#include <string>

using namespace std;


//Zustand vom Spieler
enum Zustand {
    normal,
    gesperrt
};


//Klasse Spieler
class Spieler {
private:
    //Name vom Spieler
    string name;

    //Leben vom Spieler
    int leben;

    //Zustand vom Spieler
    Zustand zustand;

public:
    //Konstruktor
    Spieler(string name);

    //Name ausgeben
    string getName();

    //Name setzen
    void setName(string name);

    //Leben ausgeben
    int getLeben();

    //Leben setzen
    void setLeben(int leben);

    //Zustand ausgeben
    Zustand getZustand();

    //Zustand setzen
    void setZustand(Zustand zustand);
};

#endif