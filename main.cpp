using namespace std;
#include <iostream>
#include "swetrki.h"
#include <regex>

int main(){
    //inicjalizuje zmienne
    string login;
    string password;
    User ThisUser;
    string Title;
    int Choice;
    int Index;
    int Choice2;
    //logowanie
    cout<<"Login: "<<endl;
    cin>> login;
    cout<<"Hasło: "<<endl;
    cin>> password;

    ThisUser.loginUser();
    // 2. Tworzymy bazę filmów
    vector<Film> FilmsBase;
    

    // Dodajmy testowy film
    Film f1;
    f1.title = "Incepcja";
    f1.keywords = "sny, sci-fi";
    FilmsBase.push_back(f1);
    //if isUserAuthenticated(ThisUser) {
    
    do {
        cout << "\n--- SYSTEM RECENZJI FILMOWYCH ---\n";
        cout << "Zalogowany jako: " << ThisUser.getLogin() << endl;
        cout << "1. Wyswietl filmy\n";
        cout << "2. Dodaj nowy film do bazy\n";
        cout << "0. Wyjdz\n";
        cout << "Wybor: ";
        cin >> Choice;

        int len = FilmsBase.size();
        switch (Choice) {
            case 1:
                for (int i=0; i<len; i++) {
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
                            FilmsBase[Index].AddReview(/*???idk*/);
                    }

            case 2 :
                
            default:
                cout<< "Podaj prawidłowy wybór"<< endl;
        }      
    } while (Choice != 0);
    return 0;
    //}
    /* dodawanie recenzji do filmu 
    cout<<"Podaj tytuł filmu: "<<endl;
                cin>>Title;
                for (int i=0;i<len; i++){
                    if (regex_match(FilmsBase[i].title, regex("*"+Title+"*"))){
                        cout<< i <<"."<< FilmsBase[i].title<< endl;
                    }
                }
                cout<<"Wybierz indeks filmu: "<<endl*/
}
