#include <iostream>
#include "MenuLogowanie.h"
using namespace std;

void czyscEkran();
void menuKsiazka ( int idUrzytkownika );
void wczytajStartAdresaci ( int usuwa, int idZmienianegoAdresata );

void MenuLogowanie::zapiszUrzytkownikaWPliku ( Urzytkownik urzytkownikLogowanie )
{
    fstream plik;
    plik.open ( "Urzytkownicy.txt", ios::out | ios::app );
    plik << urzytkownikLogowanie.id << "|";
    plik << urzytkownikLogowanie.login << "|";
    plik << urzytkownikLogowanie.haslo << "|\n";
    plik.close();
}
void MenuLogowanie::dodajUrzytkownika()
{
    Urzytkownik urzytkownikLogowanie;
    cout << "Podaj login: ";
    cin >> urzytkownikLogowanie.login;
    for ( int i = 0; i < urzytkownicy.size(); i++ )
    {
        if ( urzytkownicy[i].login == urzytkownikLogowanie.login )
        {
            czyscEkran();
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
    czyscEkran();
}
void MenuLogowanie::zalogujUrzytkownika ( )
{
    string login, haslo;
    cout << "Podaj login: " ;
    cin >> login;
    cout << "Podaj haslo: ";
    cin >> haslo;
    for ( int i = 0; i < urzytkownicy.size(); i++ )
    {
        if ( urzytkownicy[i].login == login )
        {
            czyscEkran();
            if ( urzytkownicy[i].haslo == haslo )
            {
                idUrzytkownika = urzytkownicy[i].id;
                wczytajStartAdresaci ( 0, 0 );
                menuKsiazka ( idUrzytkownika );
            }
        }
    }
    cout << "Bledny login lub haslo \n";
}
void MenuLogowanie::menu_logowanie()
{
    int x = 0;
    cout << "Wybierz :  \n";
    cout << "1. Logowanie \n";
    cout << "2. Rejestracja \n";
    cout << "9. Zakoncz program \n";
    cin >> x;
    czyscEkran();
    switch ( x )
    {
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
void MenuLogowanie::wczytajNaNowoDoPliku ()
{
    ofstream plik;
    plik.open ( "Urzytkownicy.txt" );
    plik.close();
    for ( int i = 0; i < urzytkownicy.size(); i++ )
        zapiszUrzytkownikaWPliku ( urzytkownicy[i] );
}
void MenuLogowanie::wczytajUrzytkownikaZPliku ( string daneOsoby )
{
    string wynik = "";
    int linia = 0;
    Urzytkownik urzytkownikLogowanie;
    for ( int i = 0; i <= daneOsoby.size(); i++ )
    {
        if ( daneOsoby[ i ] != '|' )
            wynik += daneOsoby[ i ];
        else if ( daneOsoby[ i ] == '|' )
        {
            linia++;
            if ( linia == 1 )
                urzytkownikLogowanie.id = atoi ( wynik.c_str() );
            if ( linia == 2 )
                urzytkownikLogowanie.login = wynik;
            if ( linia == 3 )
            {
                urzytkownikLogowanie.haslo = wynik;
                urzytkownicy.push_back ( urzytkownikLogowanie );
            }
            wynik = "";
        }
    }
}
void MenuLogowanie::wczytajStartLogowanie()
{
    string wierszZdanymi;
    ifstream plik ( "Urzytkownicy.txt" );
    if ( plik.good() == false )
        cout << "Ksiazka jest pusta \n";
    else
    {
        for ( int i = 0; plik.eof() != 1; i )
        {
            getline ( plik, wierszZdanymi );
            if ( !wierszZdanymi.empty () )
            {
                wczytajUrzytkownikaZPliku ( wierszZdanymi );
            }
        }
        plik.close();
    }
}
