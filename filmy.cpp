#include <iostream>
#include <vector>
#include "swetrki.h"
using namespace std;


void Film::dodajtytul(){
    cout << "Podaj tytuł:";
    cin.ignore(); 
    getline(cin, tytul);
}



void Film::(){
    cout << "Podaj hasła kluczowe:";
    cin.ignore();
    getline(cin, keywords);
    
}