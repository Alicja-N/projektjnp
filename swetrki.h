using namespace std;
#include <iostream>
#include <vector>
using std::vector;
using std::string;
//enum class Rank { FATALNY = 1, SLABY = 2, SREDNI = 3, DOBRY = 4,REWELACYJNY = 5};

class Review{
public:
    int rating;
    string text;
    string author;
};

class Film{
public:
    string title;
    string keywords;
    vector<Review> Reviews;
    bool AddReview(const Review& r);
    bool RemoveReview(Review& r);
    bool ViewReviews();
    int getReviewsCount() const;
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

class Data {
public:
    virtual ~Data() {}//destruktor

    virtual bool saveUsers(const vector<User>& users) = 0;
    virtual vector<User> loadUsers() = 0;

    virtual bool saveFilms(const vector<Film>& films) = 0;
    virtual vector<Film> loadFilms() = 0;
};

