using namespace std;
#include <iostream>
#include "swetrki.h"

int main(){
    // 1. Tworzymy użytkownika (na razie na sztywno)
    User aktualnyUzytkownik("admin123", "Kamil");
    aktualnyUzytkownik.loginUser(); // Logujemy go
    // aktualnyUzytkownik.setAdminStatus(true); // Opcjonalnie dajemy admina

    // 2. Tworzymy bazę filmów
    vector<Film> bazaFilmow;

    // Dodajmy testowy film
    Film f1;
    f1.title = "Incepcja";
    f1.keywords = "sny, sci-fi";
    bazaFilmow.push_back(f1);

    int wybor;
    do {
        cout << "\n--- SYSTEM RECENZJI FILMOWYCH ---\n";
        cout << "Zalogowany jako: " << aktualnyUzytkownik.getLogin() << endl;
        cout << "1. Wyswietl filmy i recenzje\n";
        cout << "2. Dodaj recenzje do filmu\n";
        cout << "3. Dodaj nowy film do bazy\n";
        cout << "0. Wyjdz\n";
        cout << "Wybor: ";
        cin >> wybor;

        int len = bazaFilmow.size();
        if (wybor==1) {
            for (int i=0; i<len; i++) {
                Film &film = bazaFilmow[i];
                cout<< "Tytuł: "<<film.title<< endl;
                cout<<"Słowa kluczowe: "<<film.keywords<<endl;
                film.ViewReviews();

            }
        }
        else if (wybor == 2) {
            string tresc;
            int ocenaNum;
            
            cout << "Wybierz film (0 - " << bazaFilmow.size()-1 << "): ";
            int filmIdx;
            cin >> filmIdx;

            if (filmIdx >= 0 && filmIdx < bazaFilmow.size()) {
                cout << "Twoja recenzja: ";
                cin.ignore(); // czyszczenie bufora
                getline(cin, tresc);
                cout << "Ocena (1-5): ";
                cin >> ocenaNum;

                Review nowa;
                nowa.autor = aktualnyUzytkownik.getLogin();
                nowa.text = tresc;
                nowa.rating = static_cast<Rank>(ocenaNum);

                bazaFilmow[filmIdx].AddReview(nowa);
                cout << "Dodano!\n";
            }
        }
        else if (wybor == 3) {
            Film nowyFilm;
            cout << "Podaj tytul filmu: ";
            cin.ignore(); // czyścimy bufor po cin >> wybor
            getline(cin, nowyFilm.title);
    
            cout << "Podaj slowa kluczowe: ";
            getline(cin, nowyFilm.keywords);

            bazaFilmow.push_back(nowyFilm);
            cout << "Film zostal dodany do bazy!\n";
        }
    } while (wybor != 0);

    return 0;
}
