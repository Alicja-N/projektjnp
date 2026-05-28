#include "swetrki.h"
#include <iostream>
#include <vector>

using namespace std;


void User::loginUser(l, password) {

    //Szukamy w administratorach
    for (const User& admin : RegisteredAdmins) {
        if (admin.login == l) {
            this->login = admin.login;
            this->name = admin.name;
            this->isAuthenticated = true;
            this->isAdmin = true;
            cout << "Zalogowano pomyślnie jako Administrator: " << this->name << endl;
            return;
        }
    }

    //Szukamy w zwykłych użytkownikach
    for (const User& user : RegisteredUsers) {
        if (user.login == l && user.password == p) {
            this->login = user.login;
            this->name = user.name;
            this->isAuthenticated = true;
            this->isAdmin = false;
            cout << "Zalogowano pomyślnie jako Użytkownik: " << this->name << endl;
            return;
        }
    }

    //Jeśli pętla nie znalazła loginu
    this->isAuthenticated = false;
    this->isAdmin = false;
    cout << "Błąd logowania: Użytkownik o podanym loginie nie istnieje." << endl;
}

bool User::checkAdmin() const {
    return isAuthenticated && isAdmin;
}

string User::getLogin() const {
    if (isAuthenticated) {
        return login;
    }
    return "Niezalogowany";
}