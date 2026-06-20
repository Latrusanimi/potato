#include "Spieler.h"


//Konstruktor
Spieler::Spieler(string name) {
    this -> name = name;
    this -> leben = 15;
    this -> zustand = normal;
}


//Name ausgeben
string Spieler::getName() {
    return name;
}


//Name setzen
void Spieler::setName(string name) {
    this -> name = name;
}


//Leben ausgeben
int Spieler::getLeben() {
    return leben;
}


//Leben setzen
void Spieler::setLeben(int leben) {
    this -> leben = leben;
}


//Zustand ausgeben
Zustand Spieler::getZustand() {
    return zustand;
}


//Zustand setzen
void Spieler::setZustand(Zustand zustand) {
    this -> zustand = zustand;
}