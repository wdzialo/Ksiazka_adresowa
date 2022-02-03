#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "MenuLogowanie.h"
using namespace std;

void czyscEkran()
{
#ifdef WIN32
    system(“cls”);
#else
    system( "clear" );
#endif
}
void menuKsiazka ( int idUrzytkownika )
{
    cout << "Menu Ksiazka \n";
}
void wczytajStartAdresaci ( int usuwa, int idZmienianegoAdresata )
{
    cout<< "weszlo \n";
}
int main()
{

    MenuLogowanie logowanie;
    logowanie.wczytajStartLogowanie();
    logowanie.menu_logowanie();

}
