#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <windows.h>

using namespace std;

string temat;
string tresc[5];
string odpA[5], odpB[5], odpC[5], odpD[5];
string poprawna[5];
string odpowiedz;
int punkty = 0;

void ustawKolorTekstu(int kolor) {
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(uchwyt, kolor);
}

void wczytajPytania() {
    int nr_linii = 1;
    int nr_pytania = 0;
    string linia;

    fstream plik("quiz_terraria.txt", ios::in);
    if (!plik.good()) {
        ustawKolorTekstu(12);
        cout << "Nie udalo sie otworzyc pliku!" << endl;
        exit(0);
    }

    while (getline(plik, linia)) {
        switch (nr_linii) {
            case 1: temat = linia; break;
            case 2: tresc[nr_pytania] = linia; break;
            case 3: odpA[nr_pytania] = linia; break;
            case 4: odpB[nr_pytania] = linia; break;
            case 5: odpC[nr_pytania] = linia; break;
            case 6: odpD[nr_pytania] = linia; break;
            case 7: poprawna[nr_pytania] = linia; break;
        }
        if (nr_linii == 7) {
            nr_linii = 1;
            nr_pytania++;
        }
        nr_linii++;
    }
    plik.close();
}

void zadawaniePytan() {
    for (int i = 0; i < 5; i++) {
        ustawKolorTekstu(11);
        cout << endl << tresc[i] << endl;

        ustawKolorTekstu(14);
        cout << "A. " << odpA[i] << endl;
        cout << "B. " << odpB[i] << endl;
        cout << "C. " << odpC[i] << endl;
        cout << "D. " << odpD[i] << endl;

        ustawKolorTekstu(7);
        cout << "Twoja odpowiedz: ";
        cin >> odpowiedz;

        transform(odpowiedz.begin(), odpowiedz.end(), odpowiedz.begin(), ::tolower);

        if (odpowiedz == poprawna[i]) {
            ustawKolorTekstu(10);
            cout << "Dobrze! Zdobywasz punkt!" << endl;
            punkty++;
        } else {
            ustawKolorTekstu(12);
            cout << "Zle! Brak punktu! Poprawna odpowiedz: " << poprawna[i] << endl;
        }
    }
}

int main() {
    wczytajPytania();

    ustawKolorTekstu(9);
    cout << "Witaj w quizie: " << temat << endl;

    zadawaniePytan();

    ustawKolorTekstu(11);
    cout << "Koniec quizu! Zdobyte punkty: " << punkty << "/5" << endl;
    return 0;
}
