using namespace std;
#include <iostream>
#include <vector>
using std::vector;
using std::string;
//enum class Rank { FATALNY = 1, SLABY = 2, SREDNI = 3, DOBRY = 4,REWELACYJNY = 5};

class Review{
public:
    string filmTitle;
    int rating;
    string text;
    string author;
};

class Film{
public:
    string title;
    string keywords;
    VectorStorage storage;
};

class VectorStorage {
    private:
        vector<Review> allReviews;
        vector<Film> allFilms;
        vector<User> allUsers;

    public:        
        bool addReview(const Review& r);
        bool removeReview(const string& filmTitle, const string& author);
        vector<Review> getReviewsForFilm(const string& filmTitle);
        int getReviewsCount(const string& filmTitle) const;
        bool addFilm(const Film& f);
        vector<Film> getAllFilms();
        bool registerUser(const User& u);
        User* findUser(const string& login);
};


class User{
public:
    string login;
    string name;
    string password;
    bool isAuthenticated;
    bool isAdmin;
    vector<User> RegisteredAdmins;
    vector<User> RegisteredUsers;
    
    bool isUserAuthenticated() const {
        return isAuthenticated;
    }
    void loginUser();
    bool checkAdmin() const;
    string getLogin() const;
};



