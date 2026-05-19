using namespace std;
#include <iostream>
#include "swetrki.h"
#include <regex>

int main(){
    //inicjalizuje zmienne
    string login;
    string password;
    User ThisUser;
    string search;
    string NewTitle;
    string NewKeywords;
    int Choice;
    int Index;
    int Choice2;
    int index;
    bool exists = false;

    //logowanie
    cout<<"Login: "<<endl;
    cin>> login;
    cout<<"Hasło: "<<endl;
    cin>> password;

    ThisUser.loginUser();
    // baza filmow - wektor z obiektami klasy Film
    vector<Film> FilmsBase;
    int len = FilmsBase.size();
    do {
        cout << "\n--- KNITTED SWEATERS ---\n";
        cout << "Zalogowany jako: " << ThisUser.getLogin() << endl;
        cout << "1. Wyswietl filmy\n";
        cout << "2. Dodaj nowy film do bazy\n";
        cout << "3.Wyszukaj film\n";
        cout << "0. Wyjdz\n";
        cout << "Wybor: ";
        cin >> Choice;

        
        switch (Choice) {
            case 0:
            {};
            case 1:
                {for (int i=0; i<len; i++) {
                    cout<< "Tytuł: "<<FilmsBase[i].title<< endl;
                }
                cout << "wybierz indeks filmu: ";
                cin >> Index;
                cout << FilmsBase[Index].title<< endl;
                cout << FilmsBase[Index].keywords<<endl;
                cout << "1.Wyświel recenzje"<<endl;
                cout << "2.Dodaj recenzje"<<endl;
                cin >> Choice2;
                    switch(Choice2){
                        case 1:
                            FilmsBase[Index].ViewReviews();
                        case 2:
                            FilmsBase[Index].AddReview();
                        default:
                            cout<< "Podaj prawidłowy wybór"<< endl;
                    }
                };
            case 2 :
                {cout << "Podaj tytuł: "<<endl;
                cin >> NewTitle;
                cout << "Podaj słowa kluczowe: " << endl;
                cin >> NewKeywords;
                Film f1;
                    f1.title = NewTitle;
                    f1.keywords = NewKeywords;
                    FilmsBase.push_back(f1);
                };
            case 3:
                {cout<<"Wyszukaj tytuł filmu lub słowa kluczowe: "<<endl;
                cin>>search;
                for (int i=0;i<len; i++){
                    if (regex_match(FilmsBase[i].title, regex("*"+search+"*"))||regex_match(FilmsBase[i].keywords, regex ("*"+search+"*"))){
                        cout<< i <<"."<< FilmsBase[i].title<< endl;
                        exists = true;
                    }
                };
                if (exists == false){
                    cout<< "Taki film nie istnieje w bazie"<< endl;
                }else {
                cout<<"podaj indeks szukanego filmu: "<<endl;
                cin>>index;
                cout<<FilmsBase[index].title<<endl;
                cout<<FilmsBase[index].keywords<<endl;
                };
                };
            default:
                {cout<< "Podaj prawidłowy wybór"<< endl;
                };
        }      
    } while (Choice != 0);
    return 0;
}
