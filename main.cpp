#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "Spieler.h"

using namespace std;


//Funktionsdeklarationen
void WarteAufWuerfeln(Spieler& spieler);
int Wuerfeln();
void FuehreZugAus(Spieler& aktiverSpieler, Spieler& gegner);
void FuehreNormalenZugAus(Spieler& aktiverSpieler, Spieler& gegner);
void ZieheLebenAb(Spieler& spieler, int schaden);
void GibSpielstandAus(Spieler& spieler1, Spieler& spieler2);
bool IstSpielBeendet(Spieler& spieler1, Spieler& spieler2);
void GibGewinnerAus(Spieler& spieler1, Spieler& spieler2);



//Hauptprogramm
int main() {
    //Zufallsgenerator starten
    srand(time(NULL));

    //Namen der Spieler
    string nameSpieler1;
    string nameSpieler2;

    //Namen einlesen
    cout << "Name von Spieler 1: ";
    getline(cin, nameSpieler1);

    cout << "Herzlich willkomen " << nameSpieler1 << "." << endl;
    cout << endl;

    cout << "Name von Spieler 2: ";
    getline(cin, nameSpieler2);

    cout << "Herzlich willkomen " << nameSpieler2 << "." << endl;

    //Spieler erstellen
    Spieler spieler1(nameSpieler1);
    Spieler spieler2(nameSpieler2);

    //Startmeldung
    cout << endl;
    cout << "Spiel startet." << endl;
    cout << "Beide Spieler haben 15 Leben." << endl;
    cout << endl;

    //Spiel laeuft, bis ein Spieler keine Leben mehr hat
    while (!IstSpielBeendet(spieler1, spieler2)) {
        //Zug Spieler 1
        FuehreZugAus(spieler1, spieler2);

        //Pruefen, ob Spiel beendet ist
        if (IstSpielBeendet(spieler1, spieler2)) {
            break;
        }

        //Spielstand ausgeben
        GibSpielstandAus(spieler1, spieler2);

        //Zug Spieler 2
        FuehreZugAus(spieler2, spieler1);

        //Spielstand ausgeben
        GibSpielstandAus(spieler1, spieler2);
    }

    //Gewinner ausgeben
    GibGewinnerAus(spieler1, spieler2);

    return 0;
}



//Warten, bis der Spieler 1 eingibt
void WarteAufWuerfeln(Spieler& spieler) {
    string eingabe;

    do {
        cout << spieler.getName() << ", gib w ein, um zu wuerfeln: ";
        cin >> eingabe;

        if (eingabe != "w") {
            cout << "Falsche Eingabe. Bitte w eingeben." << endl;
        }

    } while (eingabe != "w");
}


//Zufallszahl von 1 bis 6 erzeugen
int Wuerfeln() {
    return rand() % 6 + 1;
}


//Zug eines Spielers ausfuehren
void FuehreZugAus(Spieler& aktiverSpieler, Spieler& gegner) {
    //Pruefen, ob Spieler gesperrt ist
    if (aktiverSpieler.getZustand() == gesperrt) {
        cout << endl;
        cout << aktiverSpieler.getName() << " ist gesperrt." << endl;
        cout << aktiverSpieler.getName() << " kann versuchen, sich mit einer 6 frei zu wuerfeln." << endl;

        //Spieler versucht sich frei zu wuerfeln
        WarteAufWuerfeln(aktiverSpieler);

        //Freiwurf ausfuehren
        int freiWurf = Wuerfeln();

        //Freiwurf ausgeben
        cout << aktiverSpieler.getName() << " wuerfelt eine " << freiWurf << "." << endl;

        //Bei einer 6 ist der Spieler wieder frei
        if (freiWurf == 6) {
            aktiverSpieler.setZustand(normal);

            cout << aktiverSpieler.getName() << " ist wieder frei." << endl;
            cout << aktiverSpieler.getName() << " darf jetzt normal wuerfeln." << endl;

            //Normaler Zug nach erfolgreichem Freiwurf
            FuehreNormalenZugAus(aktiverSpieler, gegner);
        }
        else {
            cout << aktiverSpieler.getName() << " konnte sich nicht befreien." << endl;
            cout << aktiverSpieler.getName() << " verliert diese Runde." << endl;

            //Nach der gesperrten Runde ist der Spieler wieder normal
            aktiverSpieler.setZustand(normal);
        }
    }
    else {
        //Normaler Zug
        FuehreNormalenZugAus(aktiverSpieler, gegner);
    }
}


//Normalen Zug ausfuehren
void FuehreNormalenZugAus(Spieler& aktiverSpieler, Spieler& gegner) {
    //Warten, bis der Spieler wuerfeln will
    WarteAufWuerfeln(aktiverSpieler);

    //Wuerfeln
    int wuerfelZahl = Wuerfeln();

    //Wuerfelzahl ausgeben
    cout << aktiverSpieler.getName() << " wuerfelt eine " << wuerfelZahl << "." << endl;

    //Leben vom Gegner abziehen
    ZieheLebenAb(gegner, wuerfelZahl);

    //Schaden ausgeben
    cout << gegner.getName() << " verliert " << wuerfelZahl << " Leben." << endl;

    //Bei einer 6 wird der Gegner gesperrt
    if (wuerfelZahl == 6 && gegner.getLeben() > 0) {
        gegner.setZustand(gesperrt);

        cout << gegner.getName() << " wurde gesperrt." << endl;
    }
}


//Leben abziehen
void ZieheLebenAb(Spieler& spieler, int schaden) {
    //Neues Leben berechnen
    int neuesLeben = spieler.getLeben() - schaden;

    //Leben darf nicht kleiner als 0 werden
    if (neuesLeben < 0) {
        neuesLeben = 0;
    }

    //Neues Leben setzen
    spieler.setLeben(neuesLeben);
}


//Spielstand ausgeben
void GibSpielstandAus(Spieler& spieler1, Spieler& spieler2) {
    cout << endl;
    cout << "Aktueller Spielstand:" << endl;
    cout << spieler1.getName() << ": " << spieler1.getLeben() << " Leben" << endl;
    cout << spieler2.getName() << ": " << spieler2.getLeben() << " Leben" << endl;
    cout << endl;
}


//Pruefen, ob das Spiel beendet ist
bool IstSpielBeendet(Spieler& spieler1, Spieler& spieler2) {
    if (spieler1.getLeben() <= 0 || spieler2.getLeben() <= 0) {
        return true;
    }

    return false;
}


//Gewinner ausgeben
void GibGewinnerAus(Spieler& spieler1, Spieler& spieler2) {
    cout << endl;
    cout << "Spiel beendet." << endl;

    if (spieler1.getLeben() > 0) {
        cout << spieler1.getName() << " hat gewonnen." << endl;
    }
    else {
        cout << spieler2.getName() << " hat gewonnen." << endl;
    }
}