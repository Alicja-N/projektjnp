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
    int rindex;
    bool exists;
    Review r;

    
    // baza filmow - wektor z obiektami klasy Film
    vector<Film> FilmsBase;
    do {
        cout << "\n--- KNITTED SWEATERS ---\n";
        cout << "Zalogowany jako: " << ThisUser.getLogin() << endl;
        cout << "1. Wyswietl filmy\n";
        cout << "2. Dodaj nowy film do bazy\n";
        cout << "3.Wyszukaj film\n";
        cout << "4.Zaloguj się"<< endl;
        cout << "0. Wyjdz\n";
        cout << "Wybor: ";
        cin >> Choice;

        
        switch (Choice) {
            case 0:
                break;
            case 1:
                {for (int i=0; i<FilmsBase.size(); i++) {
                    cout<< "Tytuł: "<<FilmsBase[i].title<< endl;
                }
                cout << "wybierz indeks filmu: ";
                cin >> Index;
                if (Index >= 0 && Index < FilmsBase.size()) {
                cout << FilmsBase[Index].title<< endl;
                cout << FilmsBase[Index].keywords<<endl;
                cout << "1.Wyświel recenzje"<<endl;
                cout << "2.Dodaj recenzje"<<endl;
                cout << "3.Wyświetl recenzje"<<endl;
                cin >> Choice2;
                    switch(Choice2){
                        case 1:
                            FilmsBase[Index].ViewReviews();
                            break;
                        case 2:
                            FilmsBase[Index].AddReview();
                            break;
                        case 3:
                            FilmsBase[Index].ViewReviews();
                            cout << "Podaj indeks recenzji do usunięcia"<< endl;
                            cin>> rindex;
                            r = FilmsBase[Index].Reviews[rindex];
                            FilmsBase[Index].RemoveReview(r);
                            break;
                        default:
                            cout<< "Podaj prawidłowy wybór"<< endl;
                            break;
                    }
                }else{
                    cout<< "niepoprawny indeks"<< endl;
                }
                break;
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
                break;
                };
            case 3:
                {exists = false;
                cout<<"Wyszukaj tytuł filmu lub słowa kluczowe: "<<endl;
                cin>>search;
                for (int i=0;i<FilmsBase.size(); i++){
                    if (FilmsBase[i].title.find(search) != string::npos||FilmsBase[i].keywords.find(search) != string::npos){
                        cout<< i <<"."<< FilmsBase[i].title<< endl;
                        exists = true;
                    };
                };
                if (exists == false){
                    cout<< "Taki film nie istnieje w bazie"<< endl;
                }else {
                cout<<"podaj indeks szukanego filmu: "<<endl;
                cin>>index;
                cout<<FilmsBase[index].title<<endl;
                cout<<FilmsBase[index].keywords<<endl;
                };
                break;
                };
            case 4:
                {cout<<"Login: "<<endl;
                cin>> login;
                cout<<"Hasło: "<<endl;
                cin>> password;
                Thisuser User;
                    Thisuser.login = login;
                    Thisuser.password = password; 
                    ThisUser.loginUser();
                }
            default:
                {cout<< "Podaj prawidłowy wybór"<< endl;
                break;
                };
            

        }      
    } while (Choice != 0);
    return 0;
}
