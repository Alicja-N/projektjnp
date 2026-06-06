
#include <iostream>
using namespace std;
#include "swetrki.h"
#include <regex>

int main(){
    //inicjalizuje zmienne
    string login;
    string rola = "Viewer";
    string password;
    User* ThisUser;
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
    // testowe
    Admin admin1;
    admin1.setLogin("admin");
    storage.Admins.push_back(admin1); 
    Film film1;
    film1.title = "Shrek";
    film1.keywords = "ogry,osioł,bagno";
    storage.SaveFilm(film1);

    //logowanie
    cout<<"Login: "<<endl;
    cin>> login;
    cout<<"Hasło: "<<endl;
    cin>> password;

    ThisUser = storage.findUser(login);
    rola = ThisUser->getRole(); 
    if (ThisUser != nullptr) {
        cout << "Zalogowano jako: " << ThisUser->getLogin() << " (Rola: " << rola  << ")" << endl;
    } else {
    cout << "Nie znaleziono użytkownika!" << endl;
}
    do {
        cout << "\n--- KNITTED SWEATERS ---\n";
        cout << "Zalogowany jako: " << ThisUser->getLogin() << endl;
        cout << "1. Wyswietl filmy\n";
        cout << "2. Dodaj nowy film do bazy\n";
        cout << "3. Wyszukaj film\n";
        cout << "0. Wyjdz\n";
        cout << "Wybor: ";
        cin >> Choice;

        
        switch (Choice) {
            case 0:
                break;
            case 1:{
                for (int i=0; i<storage.FilmsBase.size(); i++) {
                    cout<< "Tytuł: "<<storage.FilmsBase[i].title<< endl;
                }
                cout << "wybierz indeks filmu: ";
                cin >> Index;
                if (Index >= 0 && Index < storage.FilmsBase.size()) {
                cout << storage.FilmsBase[Index].title<< endl;
                cout << storage.FilmsBase[Index].keywords<<endl;
                cout << "1.Wyświel recenzje"<<endl;
                cout << "2.Dodaj recenzje"<<endl;
                cout << "3.Usuń recenzje"<<endl;
                cin >> Choice2;
                    switch(Choice2){
                        case 1:{
                            storage.FilmsBase[Index].ViewReviews();
                            break;
                        };
                        case 2:{
                            if (rola != "Viewer"){
                                storage.FilmsBase[Index].AddReview();
                            }else{
                                cout<<  "Możesz tylko wyświetlać recenzje!";
                            };
                            break;
                        };
                        case 3:{
                            if (rola != "Viewer"&& rola != "LoggedUser"){
                                vector<Review> currentReviews = storage.getReviewsForFilm(storage.FilmsBase[Index].title);
                                if(!currentReviews.empty()) {
                                    cout << "Podaj indeks recenzji do usunięcia (0 do " << currentReviews.size()-1 << "): " << endl;
                                    cin >> rindex;
                                    if(rindex >= 0 && rindex < currentReviews.size()) {
                                        r = currentReviews[rindex];
                                        storage.FilmsBase[Index].RemoveReview(r);
                                    } else {
                                        cout << "Niepoprawny indeks recenzji." << endl;
                                    }
                                } else {
                                    cout << "Brak recenzji do usunięcia." << endl;
                                }
                            } else {
                                cout<< "Możesz tylko wyświetlać recenzje!";
                            }
                            break;
                        }
                        default:{
                            cout<< "Podaj prawidłowy wybór"<< endl;
                            break;
                        }
                    }
                 } else {
                    cout<< "niepoprawny indeks"<< endl;
                }
                break;
            }
            case  2 :
                {if (rola != "Viewer"){
                    cout << "Podaj tytuł: "<<endl;
                    cin >> NewTitle;
                    cout << "Podaj słowa kluczowe: " << endl;
                    cin >> NewKeywords;
                    Film f1;
                        f1.title = NewTitle;
                        f1.keywords = NewKeywords;
                        storage.SaveFilm(f1);
                }else{
                    cout<<  "Możesz tylko wyświetlać recenzje!";
                            }
                
                break;
                    }
            case 3:
                {exists = false;
                cout<<"Wyszukaj tytuł filmu lub słowa kluczowe: "<<endl;
                cin>>search;
                for (int i=0;i<storage.FilmsBase.size(); i++){
                    if (storage.FilmsBase[i].title.find(search) != string::npos||storage.FilmsBase[i].keywords.find(search) != string::npos){
                        cout<< i <<"."<< storage.FilmsBase[i].title<< endl;
                        exists = true;
                    };
                };
                if (exists == false){
                    cout<< "Taki film nie istnieje w bazie"<< endl;
                }else {
                cout<<"podaj indeks szukanego filmu: "<<endl;
                cin>>index;
                cout<<storage.FilmsBase[index].title<<endl;
                cout<<storage.FilmsBase[index].keywords<<endl;
                };
                break;
                };
            default:
                {cout<< "Podaj prawidłowy wybór"<< endl;
                break;
                };

        }      
    } while (Choice != 0);
    return 0;
}
