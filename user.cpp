#include "swetrki.h"
#include <iostream>
using namespace std;

User::User(std::string uLogin, std::string uName) 
    : login(uLogin), name(uName), isAuthenticated(false), isAdmin(false) {}

void User::loginUser() {
    isAuthenticated = true;
}

bool User::checkAdmin() const {
    return isAdmin && isAuthenticated;
}

std::string User::getLogin() const {
    return login;
}