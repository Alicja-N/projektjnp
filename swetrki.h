using namespace std;
#include <iostream>
#include <vector>
using std::vector;
using std::string;
enum class Rank { FATALNY = 1, SLABY = 2, SREDNI = 3, DOBRY = 4,REWELACYJNY = 5};

class Review{
public:
    Rank rating;
    string text;
    string autor;
};

class Film{
public:
    string title;
    string keywords;
    vector<Review> Reviews;
    bool AddReview(Review& r);
    bool RemoveReview(Review& r);
    bool ViewReviews();
    int getReviewsCount() const {
        return Reviews.size();
    }
};

class User{
public:
    string login;
    string name;
    bool isAuthenticated;
    bool isAdmin;
    
    User(string uLogin, string uName);
    bool isUserAuthenticated() const {
        return isAuthenticated;
    }
    void loginUser();
    bool checkAdmin() const;
    string getLogin() const;
};

