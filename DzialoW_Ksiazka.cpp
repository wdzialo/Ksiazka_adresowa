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
struct Urzytkownik {
    int id;
    string login, haslo;
};
vector<Adresat> adresaci;
vector<Urzytkownik> urzytkownicy;

int idUrzytkownika ;
int idKolejnyAdresat;

void wczytajNaNowoDoPliku ();
void wczytajStartAdresaci ( int usuwaAdresata, int idZmienianegoAdresata );
void menu_logowanie();

int poprosID () {
    int ID;
    cout << "Podaj ID adresata: ";
    cin >> ID;
    return ID;
}
void wyswietlJednegoAdresata ( int i ) {
    cout << adresaci[ i ].imie << "\n";
    cout << adresaci[ i ].nazwisko << "\n";
    cout << adresaci[ i ].telefon << "\n";
    cout << adresaci[ i ].mail << "\n";
    cout << adresaci[ i ].adres << "\n";
    cout << "id: " << adresaci[ i ].id << "\n";
}
int zamienID_na_i ( int ID ) {
    int blad = 1;
    for ( int i = 0; i < adresaci.size(); i++ ) {
        if ( adresaci[i].id == ID ) {
            blad = 0;
            return i;
        }
    }
    if ( blad == 1 ) {
        cout << "Bledne ID \n ";
        return blad = -1;
    }
}
void zapiszWszystoWAdresaci () {
    remove ( "Adresaci.txt" );
    rename ( "Adresaci_tymczasowy.txt", "Adresaci.txt" );
}
void wyloguj() {
    adresaci.clear();
    idUrzytkownika = 0;
    menu_logowanie();
}
void zmienHaslo() {
    string noweHaslo, stareHaslo;
    cout << "Podaj stare haslo: ";
    cin >> stareHaslo;
    if ( urzytkownicy[idUrzytkownika - 1].haslo == stareHaslo ) {
        cout << "Wprowadz nowe haslo: ";
        cin >> noweHaslo;
        urzytkownicy[idUrzytkownika - 1].haslo = noweHaslo;
        wczytajNaNowoDoPliku ();
        system ( "cls" );
        cout << "Haslo zminione \n";
    } else
        cout << "Bledne haslo \n";
}
void edytujAdresata ( int ID ) {
    int i = zamienID_na_i ( ID );
    int wybor = 0;
    string zmiana;
    if ( i >= 0 ) {
        cout << "1 - imie \n";
        cout << "2 - nazwisko \n";
        cout << "3 - numer telefonu \n";
        cout << "4 - email \n";
        cout << "5 - adres \n";
        cout << "6 - powrot do menu \n";
        cin >> wybor;
        if ( wybor < 6 ) {
            cin >> zmiana;
            switch ( wybor ) {
            case 1:
                adresaci[i].imie = zmiana;
                break;
            case 2:
                adresaci[i].nazwisko = zmiana;
                break;
            case 3:
                adresaci[i].telefon = zmiana;
                break;
            case 4:
                adresaci[i].mail = zmiana;
                break;
            case 5:
                adresaci[i].adres = zmiana;
                break;
            }
        }
        wczytajStartAdresaci ( 0, ID );
        system ( "cls" );
    }
}
void usunAdresata ( int ID ) {
    int i = zamienID_na_i ( ID );
    char potwierdzenie = 0;
    if ( i >= 0 ) {
        cout << "Potwierdz  t  by usunac, inny znak by anulowac :\n";
        wyswietlJednegoAdresata ( i );
        cin >> potwierdzenie;
        if ( potwierdzenie == 't' ) {
            wczytajStartAdresaci ( 1, ID );
            adresaci.erase ( adresaci.begin() +  i );
            system ( "cls" );
            cout << "Adresat id:" << ID << " usuniety \n";
        } else
            cout << "Usuwanie anulowane \n";
    }
}
void wyswietlWszystkichAdresatow() {
    if ( adresaci.size() <= 0 )
        cout << "Ksiazka jest pusta \n";
    else {
        for ( int i = 0; i < adresaci.size(); i++ ) {
            wyswietlJednegoAdresata ( i );
            cout << "\n";
        }
    }
}
void szukajOsoby ( string szukane ) {
    string wyraz;
    int znak = 0;
    cout << "Podaj szukane " << szukane << ": \n";
    cin >> wyraz;
    for ( int i = 0; i < adresaci.size(); i++ ) {
        if ( ( adresaci[i].imie == wyraz ) && ( szukane == "imie" ) ) {
            wyswietlJednegoAdresata ( i );
            znak = 1;
            cout << "\n";
        } else if ( ( adresaci[i].nazwisko == wyraz ) && ( szukane == "nazwisko" ) ) {
            wyswietlJednegoAdresata ( i );
            znak = 1;
            cout << "\n";
        } else if ( ( i == adresaci.size() - 1 ) && ( znak == 0 ) )
            cout << "Nie znaleziono " << szukane << "\n";
    }
}
string zmienAdresatNaString ( Adresat obiekt ) {
    string id_adresata =  to_string ( obiekt.id );
    string id_urzytkownika = to_string ( idUrzytkownika );
    string wierszAdresaci =  id_adresata  + "|" + id_urzytkownika  + "|" + obiekt.imie  + "|" + obiekt.nazwisko  + "|" + obiekt.telefon + "|" + obiekt.mail + "|" + obiekt.adres + "|";
    return wierszAdresaci;
}
void zapiszAdresataWPlikuAdresaci ( Adresat obiekt ) {
    fstream plik;
    plik.open ( "Adresaci.txt", ios::out | ios::app );
    plik << obiekt.id << "|";
    plik << idUrzytkownika << "|";
    plik << obiekt.imie << "|";
    plik << obiekt.nazwisko << "|";
    plik << obiekt.telefon << "|";
    plik << obiekt.mail << "|";
    plik << obiekt.adres << "| \n";
    plik.close();
}
void dodajAdresata() {
    Adresat obiekt;

    obiekt.id = idKolejnyAdresat;
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
    idKolejnyAdresat++;
    getline ( cin, obiekt.adres );
    adresaci.push_back ( obiekt );
    zapiszAdresataWPlikuAdresaci ( obiekt );
}
void menuKsiazka ( int idUrzytkownika ) {
    int x = 0;
    cout << "Wybierz : \n";
    cout << "1. Dodaj adresata \n";
    cout << "2. Wyszukaj po imieniu \n";
    cout << "3. Wyszukaj po nazwisku \n";
    cout << "4. Wyswietl wszystkich adresatow \n";
    cout << "5. Usun adresata \n";
    cout << "6. Edytuj adresata \n";
    cout << "7. Zmien haslo \n";
    cout << "8. Wyloguj sie \n";
    cout << "9. Zakoncz program \n";
    cin >> x;
    system ( "cls" );
    switch ( x ) {
    case 1:
        dodajAdresata();
        break;
    case 2:
        szukajOsoby ( "imie" );
        break;
    case 3:
        szukajOsoby ( "nazwisko" );
        break;
    case 4:
        wyswietlWszystkichAdresatow();
        break;
    case 5:
        usunAdresata ( poprosID() );
        break;
    case 6:
        edytujAdresata ( poprosID() );
        break;
    case 7:
        zmienHaslo();
        break;
    case 8:
        wyloguj();
        break;
    case 9:
        exit ( 0 );
    }
    menuKsiazka ( idUrzytkownika );
}
void zapiszWAdresaciTymczasowy ( string wiersz ) {
    fstream plik;
    plik.open ( "Adresaci_tymczasowy.txt", ios::out | ios::app );
    plik << wiersz << "\n";
    plik.close();
}
void zapiszUsunWierszAdresaci ( string daneOsoby, int usuwa, int idAdresataZmienjonego ) {
    string wynik = "";
    int wierszZapisacDoWektora;
    int linia = -1;
    Adresat obiekt;
    for ( int i = 0; i <= daneOsoby.size(); i++ ) {
        if ( daneOsoby[ i ] != '|' )
            wynik += daneOsoby[ i ];
        else if ( daneOsoby[ i ] == '|' ) {
            linia++;
            if ( linia == 0 ) {
                obiekt.id = atoi ( wynik.c_str() );
                idKolejnyAdresat = obiekt.id + 1;
            }
            if   ( linia == 1 ) {
                if ( idUrzytkownika == atoi ( wynik.c_str() ) ) {
                    wierszZapisacDoWektora = 1;
                    if ( idAdresataZmienjonego > 0 ) {
                        if ( obiekt.id == idAdresataZmienjonego ) {
                            daneOsoby = zmienAdresatNaString ( adresaci[zamienID_na_i ( idAdresataZmienjonego )] );
                            if ( usuwa != 0 )
                                daneOsoby = "";
                        }
                        wierszZapisacDoWektora = 0;
                    }
                }
                zapiszWAdresaciTymczasowy ( daneOsoby );
            }
            if ( ( linia == 2  ) && ( wierszZapisacDoWektora != 0 ) )
                obiekt.imie = wynik;
            if ( ( linia == 3  ) && ( wierszZapisacDoWektora  != 0 ) )
                obiekt.nazwisko = wynik;
            if ( ( linia == 4  ) && ( wierszZapisacDoWektora  != 0 ) )
                obiekt.telefon = wynik;
            if ( ( linia == 5  ) && ( wierszZapisacDoWektora  != 0 ) )
                obiekt.mail = wynik;
            if ( ( linia == 6  ) && ( wierszZapisacDoWektora  != 0 ) ) {
                obiekt.adres = wynik;
                adresaci.push_back ( obiekt );
            }
            wynik = "";
        }
    }
}
void wczytajStartAdresaci ( int usuwa, int idZmienianegoAdresata ) {
    if ( idZmienianegoAdresata >= 0 ) {
        string wierszZdanymi;
        idKolejnyAdresat = 1;
        remove ( "Adresaci_tymczasowy.txt" );
        ifstream plik ( "Adresaci.txt" );
        if ( plik.good() == false )
            cout << "Ksiazka jest pusta \n";
        else {
            for ( int i = 0; plik.eof() != 1; i ) {
                getline ( plik, wierszZdanymi );
                if ( !wierszZdanymi.empty () ) {
                    zapiszUsunWierszAdresaci ( wierszZdanymi, usuwa, idZmienianegoAdresata );
                }
            }
            plik.close();
            zapiszWszystoWAdresaci ();
        }
    } else
        cout << "Nieprawidolowe dane \n";
}
void zapiszUrzytkownikaWPliku ( Urzytkownik urzytkownikLogowanie ) {
    fstream plik;
    plik.open ( "Urzytkownicy.txt", ios::out | ios::app );
    plik << urzytkownikLogowanie.id << "|";
    plik << urzytkownikLogowanie.login << "|";
    plik << urzytkownikLogowanie.haslo << "|\n";
    plik.close();
}
void dodajUrzytkownika() {
    Urzytkownik urzytkownikLogowanie;
    cout << "Podaj login: ";
    cin >> urzytkownikLogowanie.login;
    for ( int i = 0; i < urzytkownicy.size(); i++ ) {
        if ( urzytkownicy[i].login == urzytkownikLogowanie.login ) {
            system ( "cls" );
            cout << "Urzytkownik juz istnieje \n";
            menu_logowanie();
        }
    }
    if ( urzytkownicy.size() == 0 )
        urzytkownikLogowanie.id = 1;
    else
        urzytkownikLogowanie.id = urzytkownicy[urzytkownicy.size() - 1].id + 1;
    cout << "Podaj haslo: ";
    cin >> urzytkownikLogowanie.haslo;
    urzytkownicy.push_back ( urzytkownikLogowanie );
    zapiszUrzytkownikaWPliku ( urzytkownikLogowanie );
    system ( "cls" );
}
void zalogujUrzytkownika ( ) {
    string login, haslo;
    cout << "Podaj login: " ;
    cin >> login;
    cout << "Podaj haslo: ";
    cin >> haslo;
    for ( int i = 0; i < urzytkownicy.size(); i++ ) {
        if ( urzytkownicy[i].login == login ) {
            system ( "cls" );
            if ( urzytkownicy[i].haslo == haslo ) {
                idUrzytkownika = urzytkownicy[i].id;
                wczytajStartAdresaci ( 0, 0 );
                menuKsiazka ( idUrzytkownika );
            }
        }
    }
    cout << "Bledny login lub haslo \n";
}
void menu_logowanie() {
    int x = 0;
    cout << "Wybierz :  \n";
    cout << "1. Logowanie \n";
    cout << "2. Rejestracja \n";
    cout << "9. Zakoncz program \n";
    cin >> x;
    system ( "cls" );
    switch ( x ) {
    case 1:
        zalogujUrzytkownika();
        break;
    case 2:
        dodajUrzytkownika();
        break;
    case 9:
        exit ( 0 );
    }
    menu_logowanie();
}
void wczytajNaNowoDoPliku () {
    ofstream plik;
    plik.open ( "Urzytkownicy.txt" );
    plik.close();
    for ( int i = 0; i < urzytkownicy.size(); i++ )
        zapiszUrzytkownikaWPliku ( urzytkownicy[i] );
}
void wczytajUrzytkownikaZPliku ( string daneOsoby ) {
    string wynik = "";
    int linia = 0;
    Urzytkownik urzytkownikLogowanie;
    for ( int i = 0; i <= daneOsoby.size(); i++ ) {
        if ( daneOsoby[ i ] != '|' )
            wynik += daneOsoby[ i ];
        else if ( daneOsoby[ i ] == '|' ) {
            linia++;
            if ( linia == 1 )
                urzytkownikLogowanie.id = atoi ( wynik.c_str() );
            if ( linia == 2 )
                urzytkownikLogowanie.login = wynik;
            if ( linia == 3 ) {
                urzytkownikLogowanie.haslo = wynik;
                urzytkownicy.push_back ( urzytkownikLogowanie );
            }
            wynik = "";
        }
    }
}
void wczytajStartLogowanie() {
    string wierszZdanymi;
    ifstream plik ( "Urzytkownicy.txt" );
    if ( plik.good() == false )
        cout << "Ksiazka jest pusta \n";
    else {
        for ( int i = 0; plik.eof() != 1; i ) {
            getline ( plik, wierszZdanymi );
            if ( !wierszZdanymi.empty () ) {
                wczytajUrzytkownikaZPliku ( wierszZdanymi );
            }
        }
        plik.close();
    }
}
int main() {
    wczytajStartLogowanie();
    menu_logowanie();

    return 0;
}
