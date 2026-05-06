using namespace std;
#include <iostream>

class Film{
public:
    string link;
    string tytuł;
    string hasłakluczowe;
    void dodajfilm();
private:
    void dodajtytuł();
    void dodajlink();
    void dodajhasłakluczowe();
};
class Recenzje{
public:
    int ocena;
    string tekst;
    string autor;
private:
    void dodajrecenzje();
};
class User{
protected:
    string username;
    string email;

};
class Viewer: public User{

};
class Logged: public Viewer{
public:
    void dodajRecenzje(Film& film, string tresc, int ocena);

};

class Admin: public Logged{
    void usunFilm(int id);
    void zbanujUzytkownika(string nick);
};
