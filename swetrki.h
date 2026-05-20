#include <vector>
#include <string>
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
    bool AddReview(); 
    bool AddReview(const Review& r);//dla testów
    bool RemoveReview(Review& r);
    bool ViewReviews();
    int getReviewsCount() const;
};

class User{
public:
    string login;
    string name;
    vector<User> RegisteredAdmins;
    vector<User> RegisteredUsers;
    bool isAuthenticated;
    bool isAdmin;
    bool isUserAuthenticated() const {
        return isAuthenticated;
    }
    void loginUser();
    bool checkAdmin() const;
    string getLogin() const;
};
