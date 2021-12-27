#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

struct Adresat {
    int id;
    string imie, nazwisko, telefon, mail, adres;
};
vector<Adresat> adresaci;

void wyswietlJednegoAdresata(int i) {
        cout << adresaci[ i ].imie << "\n";
        cout << adresaci[ i ].nazwisko << "\n";
        cout << adresaci[ i ].telefon << "\n";
        cout << adresaci[ i ].mail << "\n";
        cout << adresaci[ i ].adres<< "\n";
        cout << "id: " << adresaci[ i ].id << "\n";
}
void szukajOsoby ( string szukane ) {
    string wyraz;
    cin >> wyraz;
    for ( int i = 0; i < adresaci.size(); i++ ) {
        if (( adresaci[i].imie == wyraz ) && ( szukane == "imie" )) {
            wyswietlJednegoAdresata ( i );
            cout << "\n";
        } else if(( adresaci[i].nazwisko == wyraz ) && ( szukane == "nazwisko" )) {
            wyswietlJednegoAdresata ( i );
            cout << "\n";
        }
    }
}
int pobierzID() {
    int id;
    if ( adresaci.size() > 0 ) {
        cout << "Potaj ID adresata" << "\n";
        cin >> id;
        for ( int i = 0; i <= adresaci.size(); i++ ) {
            if ( adresaci[i].id == id )
                return id = i;
        }
    } else{
    cout << "Ksiazka jest pusta" <<"\n";
    return id = -1 ;
    }
}
void zapiszOsobeWPliku ( Adresat obiekt ) {
    fstream plik;
    plik.open( "ksiazka.txt", ios::out | ios::app );
    plik << obiekt.id << "|";
    plik << obiekt.imie << "|";
    plik << obiekt.telefon << "|";
    plik << obiekt.nazwisko << "|";
    plik << obiekt.mail << "|";
    plik << obiekt.adres << "| \n";
    plik.close();
}
void wczytajNaNowoDoPliku () {
	ofstream plik;
    plik.open ( "ksiazka.txt" );
    plik.close();
    for ( int i = 0; i < adresaci.size(); i++ )
        zapiszOsobeWPliku ( adresaci[i] );
}
void edytujOsobe() {
    int id = pobierzID();
    int x = 0;
    string zmiana;
    if ( id >= 0 ) {
        cout << "1 - imie" << "\n";
        cout << "2 - nazwisko" << "\n";
        cout << "3 - numer telefonu" << "\n";
        cout << "4 - email" << "\n";
        cout << "5 - adres" << "\n";
        cout << "6 - powrót do menu" << "\n";
        cin >> x;
        if ( x != 6 ) {
            cin >> zmiana;
            switch ( x ) {
            case 1:
                adresaci[id].imie = zmiana;
                break;
            case 2:
                adresaci[id].nazwisko = zmiana;
                break;
            case 3:
                adresaci[id].telefon = zmiana;
                break;
            case 4:
                adresaci[id].mail = zmiana;
                break;
            case 5:
                adresaci[id].adres = zmiana;
                break;
            }
            wczytajNaNowoDoPliku();
        }
    } else
        cout << "Bledne ID" << "\n";
}
void dodajOsobe() {
    Adresat obiekt;

    if(adresaci.size()==0)
        obiekt.id=1;
    else
    obiekt.id = adresaci[adresaci.size() - 1].id + 1;
    cout << "Podaj imie: ";
    cin >> obiekt.imie;
    cout << "Podaj nazwisko: ";
    cin.sync();
    getline ( cin, obiekt.nazwisko );
    cout << "Podaj nr telefonu: ";
    cin.sync();
    getline ( cin, obiekt.telefon );
    cout << "Podaj email: ";
    cin >> obiekt.mail;
    cout << "Podaj adres: ";
    cin.sync();
    getline ( cin, obiekt.adres );

    adresaci.push_back ( obiekt );
    zapiszOsobeWPliku ( obiekt );
}
void usunOsobe( ) {
    int id;
    char wybor;
    id = pobierzID();

    if ( id >= 0 ) {
        cout << "Potwierdz  t  by usunac, lub inny znak by anulowac usuwanie adresata :\n";
        wyswietlJednegoAdresata ( id );
        cin >> wybor;
        if ( wybor == 't') {
            adresaci.erase ( adresaci.begin() + id );
            wczytajNaNowoDoPliku ();
        } else
            cout << "Usuwanie anulowane" << "\n";
    } else
        cout << "Bledne ID" << "\n";
}
void wyswietl() {
    if ( adresaci.size() < 1 )
        cout << "Ksiazka jest pusta " << "\n";
    else {
        for ( int i = 0; i < adresaci.size(); i++ ) {
            wyswietlJednegoAdresata( i );
            cout << "\n";
        }
    }
}
void menu_start() {
    int x = 0;
    while ( x > 9 || x < 1 ) {
        cout << "Wybierz : " << "\n";
        cout << "1. Dodaj adresata" << "\n";
        cout << "2. Wyszukaj po imieniu" << "\n";
        cout << "3. Wyszukaj po nazwisku" << "\n";
        cout << "4. Wyswietl wszystkich adresatow" << "\n";
        cout << "5. Usun adresata" << "\n";
        cout << "6. Edytuj adresata" << "\n";
        cout << "9. Zakoncz program" << "\n";
        cin >> x;
        system("cls");
    }
    switch ( x ) {
    case 1:
        dodajOsobe();
        break;
    case 2:
        szukajOsoby("imie");
        break;
    case 3:
        szukajOsoby("nazwisko");
        break;
    case 4:
        wyswietl();
        break;
    case 5:
        usunOsobe();
        break;
    case 6:
        edytujOsobe();
        break;
    case 9:
        exit ( 0 );
    }
    menu_start();
}
void wczytajOsobeZPliku ( string daneOsoby ) {
    string wynik = "";
    int linia = 0;
    Adresat obiekt;

    for ( int i = 0; i <= daneOsoby.size(); i++ ) {
        if ( daneOsoby[ i ] != '|' )
            wynik += daneOsoby[ i ];
        else if ( daneOsoby[ i ] == '|' ) {
            linia++;
            if ( linia == 1 )
                obiekt.id = atoi ( wynik.c_str() );
            if ( linia == 2 )
                obiekt.imie = wynik;
            if ( linia == 3 )
                obiekt.nazwisko = wynik;
            if ( linia == 4 )
                obiekt.telefon = wynik;
            if ( linia == 5 )
                obiekt.mail = wynik;
            if ( linia == 6 ) {
                obiekt.adres = wynik;
                adresaci.push_back ( obiekt );
            }
            wynik = "";
        }
    }
}
void wczytajStart() {
    string wierszZdanymi;
    ifstream plik( "ksiazka.txt" );
    if ( plik.good() == false )
        cout << "Ksiazka jest pusta" << "\n";
    else {
        for ( int i = 0; plik.eof() != 1; i) {
            getline ( plik, wierszZdanymi );
            if ( !wierszZdanymi.empty () )
                wczytajOsobeZPliku ( wierszZdanymi );
        }
        plik.close();
    }
}
int main() {
    wczytajStart();
    menu_start();
    return 0;
}
