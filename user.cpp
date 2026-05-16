#include "swetrki.h"
#include <iostream>
using namespace std;
class User{
public:
    string login;
    string name;
    bool isAuthenticated;
    bool isAdmin;
    
    bool isUserAuthenticated() const {
        return isAuthenticated;
    }
    void loginUser(string login, string password);
    bool checkAdmin() const;
    string getLogin() const;
};