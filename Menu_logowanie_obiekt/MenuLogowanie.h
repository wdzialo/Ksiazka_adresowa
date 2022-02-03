#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

class MenuLogowanie
{
    int idUrzytkownika ;
    struct Urzytkownik
    {
        int id;
        string login, haslo;
    };
    vector<Urzytkownik> urzytkownicy;
    void dodajUrzytkownika() ;
    void zalogujUrzytkownika ( ) ;
    void wczytajNaNowoDoPliku () ;
    void wczytajUrzytkownikaZPliku ( string daneOsoby ) ;
    void zapiszUrzytkownikaWPliku ( Urzytkownik urzytkownikLogowanie ) ;
public :
    void menu_logowanie() ;
    void wczytajStartLogowanie() ;
};
